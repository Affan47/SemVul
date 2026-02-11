SelectCALL(SDNode *N) {


  SDValue Chain = N->getOperand(0);
  SDValue Addr = N->getOperand(1);
  SDValue InFlag = N->getOperand(N->getNumOperands() - 1);
  DebugLoc dl = N->getDebugLoc();

   if (Addr.getOpcode() == AlphaISD::GPRelLo) {
     SDValue GOT = SDValue(getGlobalBaseReg(), 0);
     Chain = CurDAG->getCopyToReg(Chain, dl, Alpha::R29, GOT, InFlag);
     InFlag = Chain.getValue(1);
     Chain = SDValue(CurDAG->getMachineNode(Alpha::BSR, dl, MVT::Other,
                                            MVT::Glue, Addr.getOperand(0),
                                            Chain, InFlag), 0);
   } else {
     Chain = CurDAG->getCopyToReg(Chain, dl, Alpha::R27, Addr, InFlag);
     InFlag = Chain.getValue(1);
     Chain = SDValue(CurDAG->getMachineNode(Alpha::JSR, dl, MVT::Other,
                                            MVT::Glue, Chain, InFlag), 0);
   }
   InFlag = Chain.getValue(1);

  ReplaceUses(SDValue(N, 0), Chain);
  ReplaceUses(SDValue(N, 1), InFlag);
}
