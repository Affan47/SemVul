DohCopy(const DOH *obj) {
  DohBase *b = (DohBase *) obj;
  DohObjInfo *objinfo;

  if (!obj)
    return 0;
  objinfo = b->type;
  if (objinfo->doh_copy) {
    DohBase *bc = (DohBase *) (objinfo->doh_copy) (b);
    if ((bc) && b->meta) {
      bc->meta = Copy(b->meta);
    }
    return (DOH *) bc;
  }
  return 0;
}
