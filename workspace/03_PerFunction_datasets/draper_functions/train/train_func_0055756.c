setupFonts(Dict *resDict) {
  Object obj1, obj2;
  Ref r;
  GfxFontDict *gfxFontDict;
  GfxFont *font;
  int i;

  if (forceRasterize) return;

  gfxFontDict = NULL;
  resDict->lookupNF("Font", &obj1);
  if (obj1.isRef()) {
    obj1.fetch(xref, &obj2);
    if (obj2.isDict()) {
      r = obj1.getRef();
      gfxFontDict = new GfxFontDict(xref, &r, obj2.getDict());
    }
    obj2.free();
  } else if (obj1.isDict()) {
    gfxFontDict = new GfxFontDict(xref, NULL, obj1.getDict());
  }
  if (gfxFontDict) {
    for (i = 0; i < gfxFontDict->getNumFonts(); ++i) {
      if ((font = gfxFontDict->getFont(i))) {
	setupFont(font, resDict);
      }
    }
    delete gfxFontDict;
  }
  obj1.free();
}
