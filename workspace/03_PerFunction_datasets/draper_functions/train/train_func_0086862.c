match(GooString *nameA, GBool boldA, GBool italicA) {
  return !strcasecmp(name->getCString(), nameA->getCString()) &&
         bold == boldA && italic == italicA;
}
