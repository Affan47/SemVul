getPageRef(int i)
{
  if (i < 1) return NULL;

  catalogLocker();
  if (i > lastCachedPage) {
     GBool cached = cachePageTree(i);
     if ( cached == gFalse) {
       return NULL;
     }
  }
  return &pageRefs[i-1];
}
