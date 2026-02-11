GetImageDepthCallBack(void *mutable_data,
                      const void *immutable_data,
                      const Image *image,
                      const PixelPacket *pixels,
                      const IndexPacket *indexes,
                      const long npixels,
                      ExceptionInfo *exception
                      )
{
  unsigned int
    *current_depth=(unsigned int *) mutable_data;

  magick_uint8_t
    *map = (magick_uint8_t *) immutable_data;

  register unsigned int
    depth;

  register long
    i;

  ARG_NOT_USED(indexes);
  ARG_NOT_USED(exception);

#if defined(HAVE_OPENMP)
#  pragma omp critical (GM_GetImageDepthCallBack)
#endif
  {
    depth=*current_depth;
  }

#if MaxMap == MaxRGB
  if (map)
    {


      for (i=0; i < npixels; i++)
        {
          depth=Max(depth,map[pixels[i].red]);
          depth=Max(depth,map[pixels[i].green]);
          depth=Max(depth,map[pixels[i].blue]);
          if (image->matte)
            depth=Max(depth,map[pixels[i].opacity]);
          if (depth == QuantumDepth)
            break;
        }
    }
#else
    {


      register unsigned int
        scale;

      ARG_NOT_USED(map);
      scale=MaxRGB / (MaxRGB >> (QuantumDepth-depth));
      i=0;
      while (i < npixels)
        {
          if ((pixels[i].red != scale*(pixels[i].red/scale)) ||
              (pixels[i].green != scale*(pixels[i].green/scale)) ||
              (pixels[i].blue != scale*(pixels[i].blue/scale)) ||
              (image->matte &&
               (pixels[i].opacity != scale*((pixels[i].opacity/scale)))))
            {
              depth++;
              if (depth == QuantumDepth)
                break;
              scale=MaxRGB / (MaxRGB >> (QuantumDepth-depth));
              continue;
            }
          i++;
        }
    }
#endif

#if defined(HAVE_OPENMP)
#  pragma omp critical (GM_GetImageDepthCallBack)
#endif
  {
    if (depth > *current_depth)
      *current_depth=depth;
  }

  return (depth >= QuantumDepth ? MagickFail : MagickPass);
}
