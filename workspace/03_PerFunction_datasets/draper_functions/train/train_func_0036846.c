SetAttributeList(AttributeList* al) {
  if (_attrlist)
    Unref(_attrlist);
  _attrlist = al;
  Resource::ref(_attrlist);

#if 0
    if (al) {
      static int hidden_symid = symbol_find("hidden");
      AttributeValue* av = al->find(hidden_symid);
      if (av)
	_gr->Hide(av->is_true());
    }
#endif
    Observable::notify();
}
