substitutePhysReg(MachineOperand &MO, unsigned Reg,
                              const TargetRegisterInfo &TRI) {
  if (MO.getSubReg()) {
    MO.substPhysReg(Reg, TRI);


    MachineInstr &MI = *MO.getParent();
    if (MO.isUse() && !MO.isUndef() &&
        (MO.isKill() || MI.isRegTiedToDefOperand(&MO-&MI.getOperand(0))))
      MI.addRegisterKilled(Reg, &TRI,  true);
  } else {
    MO.setReg(Reg);
  }
}
