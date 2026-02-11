GetMotionBlurKernel(const size_t width,const double sigma)
{
  double
    *kernel,
    normalize;

  register ssize_t
    i;


  (void) LogMagickEvent(TraceEvent,GetMagickModule(),"...");
  kernel=(double *) AcquireAlignedMemory((size_t) width,sizeof(*kernel));
  if (kernel == (double *) NULL)
    return(kernel);
  normalize=0.0;
  for (i=0; i < (ssize_t) width; i++)
  {
    kernel[i]=(double) (exp((-((double) i*i)/(double) (2.0*MagickSigma*
      MagickSigma)))/(MagickSQ2PI*MagickSigma));
    normalize+=kernel[i];
  }
  for (i=0; i < (ssize_t) width; i++)
    kernel[i]/=normalize;
  return(kernel);
}
