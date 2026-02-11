manifest_cache_find(int rid){
  int i;
  Manifest *p;
  for(i=0; i<MX_MANIFEST_CACHE; i++){
    if( manifestCache.apManifest[i] && manifestCache.apManifest[i]->rid==rid ){
      p = manifestCache.apManifest[i];
      manifestCache.apManifest[i] = 0;
      return p;
    }
  }
  return 0;
}
