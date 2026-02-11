foldAsLoad(LiveInterval *LI,
                               SmallVectorImpl<MachineInstr*> &Dead,
                               MachineRegisterInfo &MRI,
                               LiveIntervals &LIS,
                               const TargetInstrInfo &TII) {
  MachineInstr *DefMI = 0, *UseMI = 0;


  for (MachineRegisterInfo::reg_nodbg_iterator I = MRI.reg_nodbg_begin(LI->reg),
       E = MRI.reg_nodbg_end(); I != E; ++I) {
    MachineOperand &MO = I.getOperand();
    MachineInstr *MI = MO.getParent();
    if (MO.isDef()) {
      if (DefMI && DefMI != MI)
        return false;
      if (!MI->getDesc().canFoldAsLoad())
        return false;
      DefMI = MI;
    } else if (!MO.isUndef()) {
      if (UseMI && UseMI != MI)
        return false;

      if (MO.getSubReg())
        return false;
      UseMI = MI;
    }
  }
  if (!DefMI || !UseMI)
    return false;

  DEBUG(dbgs() << "Try to fold single def: " << *DefMI
               << "       into single use: " << *UseMI);

  SmallVector<unsigned, 8> Ops;
  if (UseMI->readsWritesVirtualRegister(LI->reg, &Ops).second)
    return false;

  MachineInstr *FoldMI = TII.foldMemoryOperand(UseMI, Ops, DefMI);
  if (!FoldMI)
    return false;
  DEBUG(dbgs() << "                folded: " << *FoldMI);
  LIS.ReplaceMachineInstrInMaps(UseMI, FoldMI);
  UseMI->eraseFromParent();
  DefMI->addRegisterDead(LI->reg, 0);
  Dead.push_back(DefMI);
  ++NumDCEFoldedLoads;
  return true;
}
