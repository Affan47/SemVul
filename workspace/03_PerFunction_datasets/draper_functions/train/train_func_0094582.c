RemoveAllTypes() {
  for (unsigned i = 0, e = Types.size(); i != e; ++i)
    Types[i] = EEVT::TypeSet();
  if (isLeaf()) return;
  for (unsigned i = 0, e = getNumChildren(); i != e; ++i)
    getChild(i)->RemoveAllTypes();
}
