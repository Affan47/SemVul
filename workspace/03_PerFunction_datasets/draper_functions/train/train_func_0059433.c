canClobber(const SUnit *SU, const SUnit *Op) {
  if (SU->isTwoAddress) {
    unsigned Opc = SU->getNode()->getMachineOpcode();
    const MCInstrDesc &MCID = TII->get(Opc);
    unsigned NumRes = MCID.getNumDefs();
    unsigned NumOps = MCID.getNumOperands() - NumRes;
    for (unsigned i = 0; i != NumOps; ++i) {
      if (MCID.getOperandConstraint(i+NumRes, MCOI::TIED_TO) != -1) {
        SDNode *DU = SU->getNode()->getOperand(i).getNode();
        if (DU->getNodeId() != -1 &&
            Op->OrigNode == &(*SUnits)[DU->getNodeId()])
          return true;
      }
    }
  }
  return false;
}
