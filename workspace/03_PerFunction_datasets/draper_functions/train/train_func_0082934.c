QuantumNoiseCB(void *mutable_data,
               const void *immutable_data,
               Image *image,
               PixelPacket *pixels,
               IndexPacket *indexes,
               const long npixels,
               ExceptionInfo *exception,
               const NoiseType noise_type
               )
{
  const QuantumImmutableContext
    *context=(const QuantumImmutableContext *) immutable_data;

  register long
    i;

  double
    factor;

  MagickRandomKernel
    *kernel;

  ARG_NOT_USED(mutable_data);
  ARG_NOT_USED(image);
  ARG_NOT_USED(indexes);
  ARG_NOT_USED(exception);

  kernel=AcquireMagickRandomKernel();
  factor=context->double_value/MaxRGBDouble;

  switch (context->channel)
    {
    case RedChannel:
    case CyanChannel:
      for (i=0; i < npixels; i++)
        pixels[i].red = GenerateQuantumNoise(pixels[i].red,noise_type,factor,kernel);
      break;
    case GreenChannel:
    case MagentaChannel:
      for (i=0; i < npixels; i++)
        pixels[i].green = GenerateQuantumNoise(pixels[i].green,noise_type,factor,kernel);
      break;
    case BlueChannel:
    case YellowChannel:
      for (i=0; i < npixels; i++)
        pixels[i].blue = GenerateQuantumNoise(pixels[i].blue,noise_type,factor,kernel);
      break;
    case BlackChannel:
    case MatteChannel:
    case OpacityChannel:
      for (i=0; i < npixels; i++)
        pixels[i].opacity = GenerateQuantumNoise(pixels[i].opacity,noise_type,factor,kernel);
      break;
    case UndefinedChannel:
    case AllChannels:
      for (i=0; i < npixels; i++)
        {
          pixels[i].red   = GenerateQuantumNoise(pixels[i].red,noise_type,factor,kernel);
          pixels[i].green = GenerateQuantumNoise(pixels[i].green,noise_type,factor,kernel);
          pixels[i].blue  = GenerateQuantumNoise(pixels[i].blue,noise_type,factor,kernel);
        }
      break;
    case GrayChannel:
      for (i=0; i < npixels; i++)
        {
          Quantum
            intensity;

          intensity = PixelIntensity(&pixels[i]);
          pixels[i].red = pixels[i].green = pixels[i].blue =
            GenerateQuantumNoise(intensity,noise_type,factor,kernel);
        }
      break;
    }

  return (MagickPass);
}
