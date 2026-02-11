initCache() {
  int i;


  glyphW = xMax - xMin + 3;
  glyphH = yMax - yMin + 3;
  if (aa) {
    glyphSize = glyphW * glyphH;
  } else {
    glyphSize = ((glyphW + 7) >> 3) * glyphH;
  }


  cacheAssoc = 8;
  if (glyphSize <= 256) {
    cacheSets = 8;
  } else if (glyphSize <= 512) {
    cacheSets = 4;
  } else if (glyphSize <= 1024) {
    cacheSets = 2;
  } else {
    cacheSets = 1;
  }
  cache = (Guchar *)gmallocn_checkoverflow(cacheSets* cacheAssoc, glyphSize);
  if (cache != NULL) {
    cacheTags = (SplashFontCacheTag *)gmallocn(cacheSets * cacheAssoc,
					     sizeof(SplashFontCacheTag));
    for (i = 0; i < cacheSets * cacheAssoc; ++i) {
      cacheTags[i].mru = i & (cacheAssoc - 1);
    }
  } else {
    cacheAssoc = 0;
  }
}
