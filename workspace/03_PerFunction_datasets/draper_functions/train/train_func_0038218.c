setColor(AnnotColor *color, GBool fill) {
  const double *values = color->getValues();

  switch (color->getSpace()) {
  case AnnotColor::colorCMYK:
    appearBuf->appendf("{0:.2f} {1:.2f} {2:.2f} {3:.2f} {4:c}\n",
		       values[0], values[1], values[2], values[3],
		       fill ? 'k' : 'K');
    break;
  case AnnotColor::colorRGB:
    appearBuf->appendf("{0:.2f} {1:.2f} {2:.2f} {3:s}\n",
		       values[0], values[1], values[2],
		       fill ? "rg" : "RG");
    break;
  case AnnotColor::colorGray:
    appearBuf->appendf("{0:.2f} {1:c}\n",
		       values[0],
		       fill ? 'g' : 'G');
    break;
  case AnnotColor::colorTransparent:
  default:
    break;
  }
}
