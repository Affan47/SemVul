getOpenElementInfo(Vector<OpenElementInfo> &v,
				      const StringC &rniPcdata) const
{
  v.clear();
  v.resize(tagLevel_);
  unsigned i = tagLevel_;
  for (IListIter<OpenElement> iter(openElements_);
       !iter.done() && i > 0;
       iter.next()) {
    OpenElementInfo &e = v[--i];
    e.gi = iter.cur()->type()->name();
    const LeafContentToken *token = iter.cur()->currentPosition();
    if (token && !token->isInitial()) {
      e.matchIndex = token->typeIndex() + 1;
      const ElementType *type = token->elementType();
      e.matchType = type ? type->name() : rniPcdata;
    }
    e.included = iter.cur()->included();
  }
}
