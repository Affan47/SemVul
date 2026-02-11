FilterFoldedOps(MachineInstr *MI,
                            SmallVector<unsigned, 2> &Ops,
                            unsigned &MRInfo,
                            SmallVector<unsigned, 2> &FoldOps) {
  MRInfo = 0;
  for (unsigned i = 0, e = Ops.size(); i != e; ++i) {
    unsigned OpIdx = Ops[i];
    MachineOperand &MO = MI->getOperand(OpIdx);

    if (MO.getSubReg())
      return true;
    if (MO.isDef())
      MRInfo |= (unsigned)VirtRegMap::isMod;
    else {

      if (MI->isRegTiedToDefOperand(OpIdx)) {
        MRInfo = VirtRegMap::isModRef;
        continue;
      }
      MRInfo |= (unsigned)VirtRegMap::isRef;
    }
    FoldOps.push_back(OpIdx);
  }
  return false;
}
