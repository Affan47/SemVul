removeIndirectObject(Ref r) {
  xrefLocker();
  if (r.num < 0 || r.num >= size) {
    error(errInternal, -1,"XRef::removeIndirectObject on unknown ref: {0:d}, {1:d}\n", r.num, r.gen);
    return;
  }
  XRefEntry *e = getEntry(r.num);
  if (e->type == xrefEntryFree) {
    return;
  }
  e->obj.free();
  e->type = xrefEntryFree;
  e->gen++;
  e->setFlag(XRefEntry::Updated, gTrue);
}
