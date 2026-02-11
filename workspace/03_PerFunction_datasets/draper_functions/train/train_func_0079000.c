ExpandOp_EXTRACT_ELEMENT(SDNode *N) {
  SDValue Lo, Hi;
  GetExpandedOp(N->getOperand(0), Lo, Hi);
  return cast<ConstantSDNode>(N->getOperand(1))->getZExtValue() ? Hi : Lo;
}
