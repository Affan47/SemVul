SyncImageCallBack(void *mutable_data,
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
  ARG_NOT_USED(exception);

  if (image->matte)
    {
      register const PixelPacket
        *p;

      for (i=0; i < npixels; i++)
        {
          VerifyColormapIndex(image,indexes[i]);


          p=&image->colormap[indexes[i]];
          pixels[i].red=p->red;
          pixels[i].green=p->green;
          pixels[i].blue=p->blue;
        }
    }
  else
    {
      for (i=0; i < npixels; i++)
        {
          VerifyColormapIndex(image,indexes[i]);


          pixels[i]=image->colormap[indexes[i]];
        }
    }

  return MagickPass;
}
