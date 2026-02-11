getRegsUsedByPHIs(const MachineBasicBlock &BB,
                              DenseSet<unsigned> *UsedByPhi) {
  for (const auto &MI : BB) {
    if (!MI.isPHI())
      break;
    for (unsigned i = 1, e = MI.getNumOperands(); i != e; i += 2) {
      unsigned SrcReg = MI.getOperand(i).getReg();
      UsedByPhi->insert(SrcReg);
    }
  }
}
