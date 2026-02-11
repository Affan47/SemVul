convertInitListSlice(const std::vector<unsigned> &Elements) const {
  ListRecTy *T = dynamic_cast<ListRecTy*>(getType());
  if (T == 0) return 0;

  if (Elements.size() == 1)
    return VarListElementInit::get(const_cast<TypedInit *>(this), Elements[0]);

  std::vector<Init*> ListInits;
  ListInits.reserve(Elements.size());
  for (unsigned i = 0, e = Elements.size(); i != e; ++i)
    ListInits.push_back(VarListElementInit::get(const_cast<TypedInit *>(this),
                                                Elements[i]));
  return ListInit::get(ListInits, T);
}
