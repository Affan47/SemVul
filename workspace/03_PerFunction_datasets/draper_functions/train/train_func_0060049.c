isLSAAddress(SDValue Op, SelectionDAG &DAG) {
  ConstantSDNode *C = dyn_cast<ConstantSDNode>(Op);
  if (!C) return 0;

  int Addr = C->getZExtValue();
  if ((Addr & 3) != 0 ||
      (Addr << 14 >> 14) != Addr)
    return 0;

  return DAG.getConstant((int)C->getZExtValue() >> 2, MVT::i32).getNode();
}
