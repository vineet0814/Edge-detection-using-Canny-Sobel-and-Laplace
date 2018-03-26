
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <stdint.h>
using namespace cv;
using namespace std;
int kernel_size = 3;
int scale = 1;
int delta = 0;
int ddepth = CV_16S;
int main(int argc, char** argv)
{
const char* filename = "zebras.jpg";
Mat src = imread(filename, 0);

if(src.empty())
{

cout << "can not open " << filename << endl;  //check if the file is empty
return -1;
}

Mat dst_canny,dst_sobel,dst_laplace;   //delcaring variables
Mat src_blur;


//canny edge detection
Canny(src, dst_canny, 50, 150, 3);     // applying canny edge detect
GaussianBlur( src, src_blur, Size(3,3), 0, 0, BORDER_DEFAULT ); //blurring the image to reduce the noise

//laplace edge detection
Laplacian( src_blur, dst_laplace, ddepth, kernel_size, scale, delta, BORDER_DEFAULT); //applying laplacian operator
convertScaleAbs( dst_laplace, dst_laplace );

//sobel edge detection
Mat grad_x, grad_y;
Mat abs_grad_x, abs_grad_y;
/// Gradient X
Sobel( src_blur, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
convertScaleAbs( grad_x, abs_grad_x );
// Gradient Y
Sobel( src_blur, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
convertScaleAbs( grad_y, abs_grad_y );
//Total Gradient (approximate)
addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst_sobel );


imshow("Source Image", src);
imshow("Canny Edge Detection", dst_canny);
imshow("Laplacian edge detect", dst_laplace);
imshow( "Sobel Edge Detection", dst_sobel );
waitKey();
return 0;
}
