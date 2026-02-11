MagickGetQuantumSamplesPerPixel(const QuantumType quantum_type)
{
  unsigned int
    samples=0;

  switch (quantum_type)
    {
    case UndefinedQuantum:
      samples=0;
      break;
    case IndexQuantum:
      samples=1;
      break;
    case GrayQuantum:
      samples=1;
      break;
    case IndexAlphaQuantum:
      samples=2;
      break;
    case GrayAlphaQuantum:
      samples=2;
      break;
    case RedQuantum:
      samples=1;
      break;
    case CyanQuantum:
      samples=1;
      break;
    case GreenQuantum:
      samples=1;
      break;
    case YellowQuantum:
      samples=1;
      break;
    case BlueQuantum:
      samples=1;
      break;
    case MagentaQuantum:
      samples=1;
      break;
    case AlphaQuantum:
      samples=1;
      break;
    case BlackQuantum:
      samples=1;
      break;
    case RGBQuantum:
      samples=3;
      break;
    case RGBAQuantum:
      samples=4;
      break;
    case CMYKQuantum:
      samples=4;
      break;
    case CMYKAQuantum:
      samples=5;
      break;
    case CIEYQuantum:
      samples=1;
      break;
    case CIEXYZQuantum:
      samples=3;
      break;
    }

  return samples;
}
