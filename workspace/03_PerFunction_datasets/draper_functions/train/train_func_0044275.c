match(GooString *nameA, GBool boldA, GBool italicA, GBool obliqueA, GBool fixedWidthA) {
  return !strcasecmp(name->getCString(), nameA->getCString()) &&
         bold == boldA && italic == italicA && oblique == obliqueA && fixedWidth == fixedWidthA;
}
