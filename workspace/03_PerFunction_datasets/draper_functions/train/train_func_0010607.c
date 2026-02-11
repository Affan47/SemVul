ColorspaceTypeToString(const ColorspaceType colorspace)
{
  const char
    *colorspace_type = "?";

  switch (colorspace)
    {
    case UndefinedColorspace:
      colorspace_type="Undefined";
      break;
    case CineonLogRGBColorspace:
      colorspace_type="CineonLogRGB";
      break;
    case RGBColorspace:
      colorspace_type="RGB";
      break;
    case GRAYColorspace:
      colorspace_type="Gray";
      break;
    case Rec601LumaColorspace:
      colorspace_type="Rec601Luma";
      break;
    case Rec709LumaColorspace:
      colorspace_type="Rec709Luma";
      break;
    case TransparentColorspace:
      colorspace_type="Transparent";
      break;
    case OHTAColorspace:
      colorspace_type="OHTA";
      break;
    case XYZColorspace:
      colorspace_type="XYZ";
      break;
    case Rec601YCbCrColorspace:
      colorspace_type="Rec601YCbCr";
      break;
    case Rec709YCbCrColorspace:
      colorspace_type="Rec709YCbCr";
      break;
    case YCCColorspace:
      colorspace_type="PhotoCD YCC";
      break;
    case YIQColorspace:
      colorspace_type="YIQ";
      break;
    case YPbPrColorspace:
      colorspace_type="YPbPr";
      break;
    case YUVColorspace:
      colorspace_type="YUV";
      break;
    case CMYKColorspace:
      colorspace_type="CMYK";
      break;
    case sRGBColorspace:
      colorspace_type="PhotoCD sRGB";
      break;
    case HSLColorspace:
      colorspace_type="HSL";
      break;
    case HWBColorspace:
      colorspace_type="HWB";
      break;
    case LABColorspace:
      colorspace_type="LAB";
      break;
    }
  return colorspace_type;
}
