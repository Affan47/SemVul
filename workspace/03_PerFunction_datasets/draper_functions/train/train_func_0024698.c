parse(Object *funcObj) {
  std::set<int> usedParents;
  return parse(funcObj, &usedParents);
}
