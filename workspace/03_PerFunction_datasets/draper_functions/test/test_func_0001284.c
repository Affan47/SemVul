getAddrModeSBit(const MachineInstr &MI,
                                         const MCInstrDesc &MCID) const {
  for (unsigned i = MI.getNumOperands(), e = MCID.getNumOperands(); i >= e;--i){
    const MachineOperand &MO = MI.getOperand(i-1);
    if (MO.isReg() && MO.isDef() && MO.getReg() == ARM::CPSR)
      return 1 << ARMII::S_BitShift;
  }
  return 0;
}
