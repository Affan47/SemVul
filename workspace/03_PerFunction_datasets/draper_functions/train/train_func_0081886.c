DohSetline(DOH *ho, int l) {
  DohBase *h = (DohBase *) ho;
  DohObjInfo *objinfo;
  if (!h)
    return;
  objinfo = h->type;
  if (objinfo->doh_setline)
    (objinfo->doh_setline) (h, l);
}
