runOnMachineFunction(MachineFunction &MF) {
  auto &HST = MF.getSubtarget<HexagonSubtarget>();
  auto &HRI = *HST.getRegisterInfo();
  auto &HII = *HST.getInstrInfo();

  MDT = &getAnalysis<MachineDominatorTree>();
  MachineRegisterInfo &MRI = MF.getRegInfo();
  bool Changed;

  Changed = DeadCodeElimination(MF, *MDT).run();

  const HexagonEvaluator HE(HRI, MRI, HII, MF);
  BitTracker BT(HE, MF);
  DEBUG(BT.trace(true));
  BT.run();

  MachineBasicBlock &Entry = MF.front();

  RegisterSet AIG;
  ConstGeneration ImmG(BT, HII, MRI);
  Changed |= visitBlock(Entry, ImmG, AIG);

  RegisterSet ARE;
  RedundantInstrElimination RIE(BT, HII, MRI);
  Changed |= visitBlock(Entry, RIE, ARE);

  RegisterSet ACG;
  CopyGeneration CopyG(BT, HII, MRI);
  Changed |= visitBlock(Entry, CopyG, ACG);

  RegisterSet ACP;
  CopyPropagation CopyP(HRI, MRI);
  Changed |= visitBlock(Entry, CopyP, ACP);

  Changed = DeadCodeElimination(MF, *MDT).run() || Changed;

  BT.run();
  RegisterSet ABS;
  BitSimplification BitS(BT, HII, MRI);
  Changed |= visitBlock(Entry, BitS, ABS);

  Changed = DeadCodeElimination(MF, *MDT).run() || Changed;

  if (Changed) {
    for (auto &B : MF)
      for (auto &I : B)
        I.clearKillInfo();
    DeadCodeElimination(MF, *MDT).run();
  }
  return Changed;
}
