emitMulFrmInstruction(const MachineInstr &MI) {
  const MCInstrDesc &MCID = MI.getDesc();


  unsigned Binary = getBinaryCodeForInstr(MI);


  Binary |= II->getPredicate(&MI) << ARMII::CondShift;


  Binary |= getAddrModeSBit(MI, MCID);


  unsigned OpIdx = 0;
  if (MCID.getNumDefs() == 2)
    Binary |= getMachineOpValue (MI, OpIdx++) << ARMII::RegRdLoShift;


  Binary |= getMachineOpValue(MI, OpIdx++) << ARMII::RegRdHiShift;


  Binary |= getMachineOpValue(MI, OpIdx++);


  Binary |= getMachineOpValue(MI, OpIdx++) << ARMII::RegRsShift;


  if (MCID.getNumOperands() > OpIdx &&
      !MCID.OpInfo[OpIdx].isPredicate() &&
      !MCID.OpInfo[OpIdx].isOptionalDef())
    Binary |= getMachineOpValue(MI, OpIdx) << ARMII::RegRdLoShift;

  emitWordLE(Binary);
}
