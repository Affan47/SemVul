getAttribute(StringRef Kind) const {
  for (iterator I = begin(), E = end(); I != E; ++I)
    if (I->hasAttribute(Kind))
      return *I;
  return Attribute();
}
