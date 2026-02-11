manifest_get(int rid, int cfType){
  Blob content;
  Manifest *p;
  if( !rid ) return 0;
  p = manifest_cache_find(rid);
  if( p ){
    if( cfType!=CFTYPE_ANY && cfType!=p->type ){
      manifest_cache_insert(p);
      p = 0;
    }
    return p;
  }
  content_get(rid, &content);
  p = manifest_parse(&content, rid, 0);
  if( p && cfType!=CFTYPE_ANY && cfType!=p->type ){
    manifest_destroy(p);
    p = 0;
  }
  return p;
}
