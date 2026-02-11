emitExtendInstruction(const MachineInstr &MI) {
  const MCInstrDesc &MCID = MI.getDesc();


  unsigned Binary = getBinaryCodeForInstr(MI);


  Binary |= II->getPredicate(&MI) << ARMII::CondShift;

  unsigned OpIdx = 0;


  Binary |= getMachineOpValue(MI, OpIdx++) << ARMII::RegRdShift;

  const MachineOperand &MO1 = MI.getOperand(OpIdx++);
  const MachineOperand &MO2 = MI.getOperand(OpIdx);
  if (MO2.isReg()) {


    Binary |= getMachineOpValue(MI, MO1) << ARMII::RegRnShift;


    Binary |= getMachineOpValue(MI, MO2);
    ++OpIdx;
  } else {
    Binary |= getMachineOpValue(MI, MO1);
  }


  if (MI.getOperand(OpIdx).isImm() &&
      !MCID.OpInfo[OpIdx].isPredicate() &&
      !MCID.OpInfo[OpIdx].isOptionalDef())
    Binary |= (getMachineOpValue(MI, OpIdx) / 8) << ARMII::ExtRotImmShift;

  emitWordLE(Binary);
}
