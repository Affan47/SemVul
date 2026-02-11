_vl_harris_response (float * harris,
                     float const * image,
                     vl_size width, vl_size height,
                     double step, double sigma,
                     double sigmaI, double alpha)
{
  float factor = (float) pow(sigma/step, 4.0) ;
  vl_index k ;

  float * LxLx ;
  float * LyLy ;
  float * LxLy ;

  LxLx = vl_malloc(sizeof(float) * width * height) ;
  LyLy = vl_malloc(sizeof(float) * width * height) ;
  LxLy = vl_malloc(sizeof(float) * width * height) ;

  vl_imgradient_f (LxLx, LyLy, 1, width, image, width, height, width) ;

  for (k = 0 ; k < (signed)(width * height) ; ++k) {
    float dx = LxLx[k] ;
    float dy = LyLy[k] ;
    LxLx[k] = dx*dx ;
    LyLy[k] = dy*dy ;
    LxLy[k] = dx*dy ;
  }

  vl_imsmooth_f(LxLx, width, LxLx, width, height, width,
                sigmaI / step, sigmaI / step) ;

  vl_imsmooth_f(LyLy, width, LyLy, width, height, width,
                sigmaI / step, sigmaI / step) ;

  vl_imsmooth_f(LxLy, width, LxLy, width, height, width,
                sigmaI / step, sigmaI / step) ;

  for (k = 0 ; k < (signed)(width * height) ; ++k) {
    float a = LxLx[k] ;
    float b = LyLy[k] ;
    float c = LxLy[k] ;

    float determinant = a * b - c * c ;
    float trace = a + b ;

    harris[k] = factor * (determinant - alpha * (trace * trace)) ;
  }

  vl_free(LxLy) ;
  vl_free(LyLy) ;
  vl_free(LxLx) ;
}
