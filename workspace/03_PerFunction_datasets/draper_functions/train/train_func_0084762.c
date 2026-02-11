visitUMULO(SDNode *N) {

  if (ConstantSDNode *C2 = dyn_cast<ConstantSDNode>(N->getOperand(1)))
    if (C2->getAPIntValue() == 2)
      return DAG.getNode(ISD::UADDO, N->getDebugLoc(), N->getVTList(),
                         N->getOperand(0), N->getOperand(0));

  return SDValue();
}
