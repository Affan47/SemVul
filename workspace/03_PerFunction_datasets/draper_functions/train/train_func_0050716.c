isContradictoryImpl(const Matcher *M) const {
  if (const CheckOpcodeMatcher *COM = dyn_cast<CheckOpcodeMatcher>(M)) {


    return COM->getOpcode().getEnumName() != getOpcode().getEnumName();
  }


  if (const CheckTypeMatcher *CT = dyn_cast<CheckTypeMatcher>(M)) {

    if (CT->getResNo() >= getOpcode().getNumResults())
      return true;

    MVT::SimpleValueType NodeType = getOpcode().getKnownType(CT->getResNo());
    if (NodeType != MVT::Other)
      return TypesAreContradictory(NodeType, CT->getType());
  }

  return false;
}
