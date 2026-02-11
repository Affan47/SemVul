GaussianBlurImageChannel(const Image *image,
  const ChannelType channel,const double radius,const double sigma,
  ExceptionInfo *exception)
{
  Image
    *blur_image;

  blur_image=GaussianBlurImage(image,radius,sigma,exception);
  if (blur_image != (Image *) NULL)
    (void) ImportImageChannelsMasked(image,blur_image,channel);

  return blur_image;
}
