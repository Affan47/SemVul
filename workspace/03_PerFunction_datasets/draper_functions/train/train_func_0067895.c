hvtocbmap(HV *hv){
  HE *entry;
  STRLEN vsiz;
  CBMAP *map;
  char *kbuf, *vbuf;
  SV *val;
  I32 ksiz;
  map = cbmapopenex(31);
  hv_iterinit(hv);
  while((entry = hv_iternext(hv)) != NULL){
    kbuf = hv_iterkey(entry, &ksiz);
    val = hv_iterval(hv, entry);
    vbuf = SvPV(val, vsiz);
    cbmapput(map, kbuf, (int)ksiz, vbuf, (int)vsiz, FALSE);
  }
  return map;
}
