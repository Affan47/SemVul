MagickCompositeImageUnderColorPixels(void *mutable_data,
				     const void *immutable_data,
				     Image *image,
				     PixelPacket * restrict pixels,
				     IndexPacket * restrict indexes,
				     const long npixels,
				     ExceptionInfo *exception)
{
  const PixelPacket
    * restrict background_color = (const PixelPacket *) immutable_data;

  register long
    i;

  ARG_NOT_USED(mutable_data);
  ARG_NOT_USED(image);
  ARG_NOT_USED(indexes);
  ARG_NOT_USED(exception);

  for (i=0; i < npixels; i++)
    {
      AlphaCompositePixel(&pixels[i],&pixels[i],pixels[i].opacity,background_color,
			  background_color->opacity);
      pixels[i].opacity=OpaqueOpacity;
    }

  return MagickPass;
}
