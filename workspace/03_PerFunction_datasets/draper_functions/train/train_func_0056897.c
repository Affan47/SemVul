HSLToRGBTransform(void *mutable_data,
                  const void *immutable_data,
                  Image *image,
                  PixelPacket *pixels,
                  IndexPacket *indexes,
                  const long npixels,
                  ExceptionInfo *exception)
{


  register long
    i;

  ARG_NOT_USED(mutable_data);
  ARG_NOT_USED(immutable_data);
  ARG_NOT_USED(image);
  ARG_NOT_USED(indexes);
  ARG_NOT_USED(exception);

  for (i=0; i < npixels; i++)
    {
      HSLTransform((double) pixels[i].red/MaxRGB,(double) pixels[i].green/MaxRGB,
                   (double) pixels[i].blue/MaxRGB,&pixels[i].red,&pixels[i].green,&pixels[i].blue);
    }

  return MagickPass;
}
