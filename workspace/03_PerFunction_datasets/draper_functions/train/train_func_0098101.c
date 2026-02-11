isConstFalseVal(const SDNode *N) const {
  if (!N)
    return false;

  const ConstantSDNode *CN = dyn_cast<ConstantSDNode>(N);
  if (!CN) {
    const BuildVectorSDNode *BV = dyn_cast<BuildVectorSDNode>(N);
    if (!BV)
      return false;

    BitVector UndefElements;
    CN = BV->getConstantSplatNode(&UndefElements);


    if (!CN || UndefElements.none())
      return false;
  }

  if (getBooleanContents(N->getValueType(0)) == UndefinedBooleanContent)
    return !CN->getAPIntValue()[0];

  return CN->isNullValue();
}
