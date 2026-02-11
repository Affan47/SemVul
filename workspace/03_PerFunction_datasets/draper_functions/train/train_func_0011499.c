CompositeOperatorToString(const CompositeOperator composite_op)
{
  const char
    *composite_op_text = "?";

  switch (composite_op)
    {
    case UndefinedCompositeOp:
      composite_op_text = "Undefined";
      break;
    case OverCompositeOp:
      composite_op_text = "Over";
      break;
    case InCompositeOp:
      composite_op_text = "In";
      break;
    case OutCompositeOp:
      composite_op_text = "Out";
      break;
    case AtopCompositeOp:
      composite_op_text = "Atop";
      break;
    case XorCompositeOp:
      composite_op_text = "Xor";
      break;
    case PlusCompositeOp:
      composite_op_text = "Plus";
      break;
    case MinusCompositeOp:
      composite_op_text = "Minus";
      break;
    case AddCompositeOp:
      composite_op_text = "Add";
      break;
    case SubtractCompositeOp:
      composite_op_text = "Subtract";
      break;
    case DifferenceCompositeOp:
      composite_op_text = "Difference";
      break;
    case MultiplyCompositeOp:
      composite_op_text = "Multiply";
      break;
    case BumpmapCompositeOp:
      composite_op_text = "Bumpmap";
      break;
    case CopyCompositeOp:
      composite_op_text = "Copy";
      break;
    case CopyRedCompositeOp:
      composite_op_text = "CopyRed";
      break;
    case CopyGreenCompositeOp:
      composite_op_text = "CopyGreen";
      break;
    case CopyBlueCompositeOp:
      composite_op_text = "CopyBlue";
      break;
    case CopyOpacityCompositeOp:
      composite_op_text = "CopyOpacity";
      break;
    case ClearCompositeOp:
      composite_op_text = "Clear";
      break;
    case DissolveCompositeOp:
      composite_op_text = "Dissolve";
      break;
    case DisplaceCompositeOp:
      composite_op_text = "Displace";
      break;
    case ModulateCompositeOp:
      composite_op_text = "Modulate";
      break;
    case ThresholdCompositeOp:
      composite_op_text = "Threshold";
      break;
    case NoCompositeOp:
      composite_op_text = "No";
      break;
    case DarkenCompositeOp:
      composite_op_text = "Darken";
      break;
    case LightenCompositeOp:
      composite_op_text = "Lighten";
      break;
    case HueCompositeOp:
      composite_op_text = "Hue";
      break;
    case SaturateCompositeOp:
      composite_op_text = "Saturate";
      break;
    case ColorizeCompositeOp:
      composite_op_text = "Colorize";
      break;
    case LuminizeCompositeOp:
      composite_op_text = "Luminize";
      break;
    case ScreenCompositeOp:
      composite_op_text = "Screen";
      break;
    case OverlayCompositeOp:
      composite_op_text = "Overlay";
      break;
    case CopyCyanCompositeOp:
      composite_op_text = "CopyCyan";
      break;
    case CopyMagentaCompositeOp:
      composite_op_text = "CopyMagenta";
      break;
    case CopyYellowCompositeOp:
      composite_op_text = "CopyYellow";
      break;
    case CopyBlackCompositeOp:
      composite_op_text = "CopyBlack";
      break;
    case DivideCompositeOp:
      composite_op_text = "Divide";
      break;
    }

  return composite_op_text;
}
