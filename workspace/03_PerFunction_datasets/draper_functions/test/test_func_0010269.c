DohGetc(DOH *obj) {
  static DOH *lastdoh = 0;
  DohBase *b = (DohBase *) obj;
  DohObjInfo *objinfo;
  if (obj == lastdoh) {
    objinfo = b->type;
    return (objinfo->doh_file->doh_getc) (b);
  }
  if (DohCheck(obj)) {
    objinfo = b->type;
    if (objinfo->doh_file->doh_getc) {
      lastdoh = obj;
      return (objinfo->doh_file->doh_getc) (b);
    }
    return EOF;
  }
  return fgetc((FILE *) b);
}
