setModifiedObject (Object* o, Ref r) {
  if (r.num < 0 || r.num >= size) {
    error(-1,"XRef::setModifiedObject on unknown ref: %i, %i\n", r.num, r.gen);
    return;
  }
  XRefEntry *e = getEntry(r.num);
  e->obj.free();
  o->copy(&(e->obj));
  e->updated = true;
}
