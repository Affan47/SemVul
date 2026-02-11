numberRCValSuccInSU(SUnit *SU,
                                                    unsigned RCId) {
  unsigned NumberDeps = 0;
  for (SUnit::const_succ_iterator I = SU->Succs.begin(), E = SU->Succs.end();
       I != E; ++I) {
    if (I->isCtrl())
      continue;

    SUnit *SuccSU = I->getSUnit();
    const SDNode *ScegN = SuccSU->getNode();
    if (!ScegN)
      continue;


    switch (ScegN->getOpcode()) {
      default:  break;
      case ISD::TokenFactor:    break;
      case ISD::CopyFromReg:    break;
      case ISD::CopyToReg:      NumberDeps++;  break;
      case ISD::INLINEASM:      break;
    }
    if (!ScegN->isMachineOpcode())
      continue;

    for (unsigned i = 0, e = ScegN->getNumOperands(); i != e; ++i) {
      const SDValue &Op = ScegN->getOperand(i);
      MVT VT = Op.getNode()->getSimpleValueType(Op.getResNo());
      if (TLI->isTypeLegal(VT)
          && (TLI->getRegClassFor(VT)->getID() == RCId)) {
        NumberDeps++;
        break;
      }
    }
  }
  return NumberDeps;
}
