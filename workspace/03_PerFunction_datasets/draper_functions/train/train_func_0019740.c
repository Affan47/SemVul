opSetStrokeRGBColor(Object args[], int numArgs) {
  Object obj;
  GfxColorSpace *colorSpace = NULL;
  GfxColor color;
  int i;

  state->setStrokePattern(NULL);
  res->lookupColorSpace("DefaultRGB", &obj);
  if (!obj.isNull()) {
    colorSpace = GfxColorSpace::parse(&obj, this);
  }
  if (colorSpace == NULL) {
    colorSpace = new GfxDeviceRGBColorSpace();
  }
  obj.free();
  state->setStrokeColorSpace(colorSpace);
  out->updateStrokeColorSpace(state);
  for (i = 0; i < 3; ++i) {
    color.c[i] = dblToCol(args[i].getNum());
  }
  state->setStrokeColor(&color);
  out->updateStrokeColor(state);
}
