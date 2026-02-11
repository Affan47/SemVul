cbmaptoobj(CBMAP *map){
  const char *kbuf, *vbuf;
  int ksiz, vsiz;
  VALUE obj;
  obj = rb_hash_new();
  cbmapiterinit(map);
  while((kbuf = cbmapiternext(map, &ksiz)) != NULL){
    vbuf = cbmapiterval(kbuf, &vsiz);
    rb_hash_aset(obj, rb_str_new(kbuf, ksiz), rb_str_new(vbuf, vsiz));
  }
  return obj;
}
