CompositeModulusSubtract(const MagickPixelPacket *p,
  const MagickPixelPacket *q, const ChannelType channel,
  MagickPixelPacket *composite)
{
  if ( (channel & SyncChannels) != 0 ) {
    MagickRealType
      Sa,
      Da,
      gamma;

    Sa=1.0-QuantumScale*p->opacity;
    Da=1.0-QuantumScale*q->opacity;
    gamma = RoundToUnity(Sa+Da-Sa*Da);
    composite->opacity=(MagickRealType) QuantumRange*(1.0-gamma);
    gamma=MagickEpsilonReciprocal(gamma);
    composite->red=ModulusSubtract(p->red,Sa,q->red,Da);
    composite->green=ModulusSubtract(p->green,Sa,q->green,Da);
    composite->blue=ModulusSubtract(p->blue,Sa,q->blue,Da);
    if (q->colorspace == CMYKColorspace)
      composite->index=ModulusSubtract(p->index,Sa,q->index,Da);
  }
  else {
    if ( (channel & AlphaChannel) != 0 )
      composite->opacity=QuantumRange-ModulusSubtract(QuantumRange-p->opacity,
           1.0,QuantumRange-q->opacity,1.0);
    if ( (channel & RedChannel) != 0 )
      composite->red=ModulusSubtract(p->red,1.0,q->red,1.0);
    if ( (channel & GreenChannel) != 0 )
      composite->green=ModulusSubtract(p->green,1.0,q->green,1.0);
    if ( (channel & BlueChannel) != 0 )
      composite->blue=ModulusSubtract(p->blue,1.0,q->blue,1.0);
    if ( (channel & IndexChannel) != 0 && q->colorspace == CMYKColorspace)
      composite->index=ModulusSubtract(p->index,1.0,q->index,1.0);
  }
}
