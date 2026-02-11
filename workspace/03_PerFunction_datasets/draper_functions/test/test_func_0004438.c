SelectBRIND(SDNode *N) {
  DebugLoc dl = N->getDebugLoc();

  SDValue Chain = N->getOperand(0);
  SDValue Addr = N->getOperand(1);
  if (Addr->getOpcode() != ISD::INTRINSIC_W_CHAIN)
    return 0;
  unsigned IntNo = cast<ConstantSDNode>(Addr->getOperand(1))->getZExtValue();
  if (IntNo != Intrinsic::xcore_checkevent)
    return 0;
  SDValue nextAddr = Addr->getOperand(2);
  SDValue CheckEventChainOut(Addr.getNode(), 1);
  if (!CheckEventChainOut.use_empty()) {


    SDValue CheckEventChainIn = Addr->getOperand(0);
    SDValue NewChain = replaceInChain(CurDAG, Chain, CheckEventChainOut,
                                      CheckEventChainIn);
    if (!NewChain.getNode())
      return 0;
    Chain = NewChain;
  }


  SDValue constOne = getI32Imm(1);
  SDValue Glue =
    SDValue(CurDAG->getMachineNode(XCore::SETSR_branch_u6, dl, MVT::Glue,
                                   constOne, Chain), 0);
  Glue =
    SDValue(CurDAG->getMachineNode(XCore::CLRSR_branch_u6, dl, MVT::Glue,
                                   constOne, Glue), 0);
  if (nextAddr->getOpcode() == XCoreISD::PCRelativeWrapper &&
      nextAddr->getOperand(0)->getOpcode() == ISD::TargetBlockAddress) {
    return CurDAG->SelectNodeTo(N, XCore::BRFU_lu6, MVT::Other,
                                nextAddr->getOperand(0), Glue);
  }
  return CurDAG->SelectNodeTo(N, XCore::BAU_1r, MVT::Other, nextAddr, Glue);
}
