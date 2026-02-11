OpaqueImageCallBack(void *mutable_data,
                      const void *immutable_data,
                      Image *image,
                      PixelPacket *pixels,
                      IndexPacket *indexes,
                      const long npixels,
                      ExceptionInfo *exception)
{
  const OpaqueImageOptions_t
    options = *((const OpaqueImageOptions_t *) immutable_data);

  register long
    i;

  ARG_NOT_USED(mutable_data);
  ARG_NOT_USED(image);
  ARG_NOT_USED(indexes);
  ARG_NOT_USED(exception);

  if (options.fuzz == 0.0)
    {
      for (i=0; i < npixels; i++)
        {
          if (ColorMatch(&pixels[i],&options.target))
            pixels[i]=options.fill;
        }
    }
  else
    {
      for (i=0; i < npixels; i++)
        {
          if (FuzzyColorMatch(&pixels[i],&options.target,options.fuzz))
            pixels[i]=options.fill;
        }
    }

  return MagickPass;
}
