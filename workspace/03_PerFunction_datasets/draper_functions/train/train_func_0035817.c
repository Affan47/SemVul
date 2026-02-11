begin(GfxState *state, GooString *text) {
  if (actualText)
    delete actualText;
  actualText = new GooString(text);
  actualTextNBytes = 0;
}
