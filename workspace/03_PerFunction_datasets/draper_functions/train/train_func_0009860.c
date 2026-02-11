AlphaBlendMagickPixelPacket(const Image *image,
  const PixelPacket *color,const IndexPacket *indexes,MagickPixelPacket *pixel,
  MagickRealType *alpha)
{
  if (image->matte == MagickFalse)
    {
      *alpha=1.0;
      pixel->red=(MagickRealType) GetPixelRed(color);
      pixel->green=(MagickRealType) GetPixelGreen(color);
      pixel->blue=(MagickRealType) GetPixelBlue(color);
      pixel->opacity=(MagickRealType) GetPixelOpacity(color);
      pixel->index=0.0;
      if (((image->colorspace == CMYKColorspace) ||
           (image->storage_class == PseudoClass)) &&
          (indexes != (const IndexPacket *) NULL))
        pixel->index=(MagickRealType) GetPixelIndex(indexes);
      return;
    }
  *alpha=QuantumScale*GetPixelAlpha(color);
  pixel->red=(*alpha*GetPixelRed(color));
  pixel->green=(*alpha*GetPixelGreen(color));
  pixel->blue=(*alpha*GetPixelBlue(color));
  pixel->opacity=(MagickRealType) GetPixelOpacity(color);
  pixel->index=0.0;
  if (((image->colorspace == CMYKColorspace) ||
       (image->storage_class == PseudoClass)) &&
      (indexes != (const IndexPacket *) NULL))
    pixel->index=(*alpha*GetPixelIndex(indexes));
}
