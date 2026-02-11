loadOpenTypeCFFFont(SplashFontFileID *idA,
							SplashFontSrc *src) {
  FoFiTrueType *ff;
  Gushort *cidToGIDMap;
  int nCIDs;
  SplashFontFile *ret;

  cidToGIDMap = NULL;
  nCIDs = 0;
  if (!useCIDs) {
    if (src->isFile) {
      ff = FoFiTrueType::load(src->fileName->getCString());
    } else {
      ff = FoFiTrueType::make(src->buf, src->bufLen);
    }
    if (ff) {
      if (ff->isOpenTypeCFF()) {
	cidToGIDMap = ff->getCIDToGIDMap(&nCIDs);
      }
      delete ff;
    }
  }
  ret = SplashFTFontFile::loadCIDFont(this, idA, src,
				      cidToGIDMap, nCIDs);
  if (!ret) {
    gfree(cidToGIDMap);
  }
  return ret;
}
