DohIsMapping(const DOH *obj) {
  DohBase *b = (DohBase *) obj;
  DohObjInfo *objinfo;
  if (!DohCheck(b))
    return 0;
  objinfo = b->type;
  if (objinfo->doh_hash)
    return 1;
  else
    return 0;
}
