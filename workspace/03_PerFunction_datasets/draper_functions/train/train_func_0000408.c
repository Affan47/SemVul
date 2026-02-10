matches (CTypeInfo *ctype) const {
  return ctype->TypeAddress () && base ()->matches (ctype->BaseType ());
}
