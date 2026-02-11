loadCIDFont(SplashFontFileID *idA,
					      SplashFontSrc *src) {
  SplashFontFile *fontFile;

  fontFile = NULL;
#if HAVE_FREETYPE_FREETYPE_H || HAVE_FREETYPE_H
  if (!fontFile && ftEngine) {
    fontFile = ftEngine->loadCIDFont(idA, src);
  }
#endif

#ifndef _WIN32


  if (src->isFile)
    src->unref();
#endif

  return fontFile;
}
