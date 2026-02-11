funcDCM_BitsAllocated(Image *image,DicomStream *dcm,ExceptionInfo *exception)
{
  ARG_NOT_USED(image);
  ARG_NOT_USED(exception);

  dcm->bits_allocated=dcm->datum;
  dcm->bytes_per_pixel=1;
  if (dcm->datum > 8)
    dcm->bytes_per_pixel=2;
  return MagickPass;
}
