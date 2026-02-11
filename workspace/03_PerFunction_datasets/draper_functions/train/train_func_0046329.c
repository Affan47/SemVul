isIdenticalTo(const Instruction *I) const {
  return isIdenticalToWhenDefined(I) &&
         SubclassOptionalData == I->SubclassOptionalData;
}
