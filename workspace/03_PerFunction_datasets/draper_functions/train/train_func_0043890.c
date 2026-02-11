IsColorSimilar(const Image *image,
  const PixelPacket *p,const PixelPacket *q)
{
  MagickRealType
    fuzz,
    pixel;

  register MagickRealType
    distance,
    scale;

  if ((image->fuzz == 0.0) && (image->matte == MagickFalse))
    return(IsColorEqual(p,q));
  fuzz=MagickMax(image->fuzz,MagickSQ1_2)*MagickMax(image->fuzz,MagickSQ1_2);
  scale=1.0;
  distance=0.0;
  if (image->matte != MagickFalse)
    {


      pixel=(MagickRealType) ((image->matte != MagickFalse ? GetPixelOpacity(p) :
        OpaqueOpacity)-(image->matte != MagickFalse ? q->opacity :
        OpaqueOpacity));
      distance=pixel*pixel;
      if (distance > fuzz)
        return(MagickFalse);


      scale=(QuantumScale*GetPixelAlpha(p));
      scale*=(QuantumScale*GetPixelAlpha(q));
      if (scale <= MagickEpsilon)
        return(MagickTrue);
    }


  distance*=3.0;
  fuzz*=3.0;
  pixel=(MagickRealType) GetPixelRed(p)-GetPixelRed(q);
  if ((image->colorspace == HSLColorspace) ||
      (image->colorspace == HSBColorspace) ||
      (image->colorspace == HWBColorspace))
    {


      if (fabs((double) pixel) > (QuantumRange/2))
        pixel-=QuantumRange;
      pixel*=2;
    }
  distance+=scale*pixel*pixel;
  if (distance > fuzz)
    return(MagickFalse);
  pixel=(MagickRealType) GetPixelGreen(p)-q->green;
  distance+=scale*pixel*pixel;
  if (distance > fuzz)
    return(MagickFalse);
  pixel=(MagickRealType) GetPixelBlue(p)-q->blue;
  distance+=scale*pixel*pixel;
  if (distance > fuzz)
    return(MagickFalse);
  return(MagickTrue);
}
