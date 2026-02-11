useCMap(CMapCache *cache, char *useName) {
  GooString *useNameStr;
  CMap *subCMap;

  useNameStr = new GooString(useName);
  subCMap = cache->getCMap(collection, useNameStr, NULL);
  delete useNameStr;
  if (!subCMap) {
    return;
  }
  copyVector(vector, subCMap->vector);
  subCMap->decRefCnt();
}
