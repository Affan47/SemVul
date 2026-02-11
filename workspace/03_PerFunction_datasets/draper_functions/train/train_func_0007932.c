RGBToCineonLogTransform(void *mutable_data,
                        const void *immutable_data,
                        Image *image,
                        PixelPacket *pixels,
                        IndexPacket *indexes,
                        const long npixels,
                        ExceptionInfo *exception)
{


  const unsigned int
    *logmap = (const unsigned int *) immutable_data;

  register long
    i;

  ARG_NOT_USED(mutable_data);
  ARG_NOT_USED(image);
  ARG_NOT_USED(indexes);
  ARG_NOT_USED(exception);

  for (i=0; i < npixels; i++)
    {
      pixels[i].red   = logmap[ScaleQuantumToMap(pixels[i].red)];
      pixels[i].green = logmap[ScaleQuantumToMap(pixels[i].green)];
      pixels[i].blue  = logmap[ScaleQuantumToMap(pixels[i].blue)];
    }

  return MagickPass;
}
