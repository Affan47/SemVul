BlurredImageAndDerivatives(const Array3Df &in,
                                double sigma,
                                Array3Df *blurred_image,
                                Array3Df *gradient_x,
                                Array3Df *gradient_y) {
  Vec kernel, derivative;
  ComputeGaussianKernel(sigma, &kernel, &derivative);
  Array3Df tmp;


  ConvolveVertical(in, kernel, &tmp);
  ConvolveHorizontal(tmp, kernel, blurred_image);


  ConvolveHorizontal(tmp, derivative, gradient_x);


  ConvolveHorizontal(in, kernel, &tmp);
  ConvolveVertical(tmp, derivative, gradient_y);
}
