opSetStrokeCMYKColor(Object args[], int numArgs) {
  GfxColor color;
  int i;

  state->setStrokePattern(NULL);
  state->setStrokeColorSpace(new GfxDeviceCMYKColorSpace());
  for (i = 0; i < 4; ++i) {
    color.c[i] = dblToCol(args[i].getNum());
  }
  state->setStrokeColor(&color);
  builder->updateStyle(state);
}
