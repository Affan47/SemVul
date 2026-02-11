processBlock(MachineBasicBlock &B,
      const RegisterSet &AVs) {
  bool Changed = false;
  RegisterSet AVB = AVs;
  RegisterSet Defs;

  for (auto I = B.begin(), E = B.end(); I != E; ++I, AVB.insert(Defs)) {
    MachineInstr *MI = &*I;
    Defs.clear();
    HBS::getInstrDefs(*MI, Defs);

    unsigned Opc = MI->getOpcode();
    if (Opc == TargetOpcode::COPY || Opc == TargetOpcode::REG_SEQUENCE)
      continue;

    if (MI->mayStore()) {
      bool T = genStoreUpperHalf(MI);
      T = T || genStoreImmediate(MI);
      Changed |= T;
      continue;
    }

    if (Defs.count() != 1)
      continue;
    const MachineOperand &Op0 = MI->getOperand(0);
    if (!Op0.isReg() || !Op0.isDef())
      continue;
    BitTracker::RegisterRef RD = Op0;
    if (!BT.has(RD.Reg))
      continue;
    const TargetRegisterClass *FRC = HBS::getFinalVRegClass(RD, MRI);
    const BitTracker::RegisterCell &RC = BT.lookup(RD.Reg);

    if (FRC->getID() == Hexagon::DoubleRegsRegClassID) {
      bool T = genPackhl(MI, RD, RC);
      Changed |= T;
      continue;
    }

    if (FRC->getID() == Hexagon::IntRegsRegClassID) {
      bool T = genExtractHalf(MI, RD, RC);
      T = T || genCombineHalf(MI, RD, RC);
      T = T || genExtractLow(MI, RD, RC);
      Changed |= T;
      continue;
    }

    if (FRC->getID() == Hexagon::PredRegsRegClassID) {
      bool T = simplifyTstbit(MI, RD, RC);
      Changed |= T;
      continue;
    }
  }
  return Changed;
}
