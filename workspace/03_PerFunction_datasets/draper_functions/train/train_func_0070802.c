emitMiscInstruction(const MachineInstr &MI) {
  unsigned Opcode = MI.getDesc().Opcode;

  unsigned Binary = getBinaryCodeForInstr(MI);

  if (Opcode == ARM::FCONSTS) {
    unsigned Imm = getMachineOpValue(MI, 1);
    Binary &= ~(0x780000 >> 19);
    Binary |= (Imm & 0x780000) >> 19;
    Binary &= ~(0x3800000 >> 7);
    Binary |= (Imm & 0x3800000) >> 7;
    Binary = VFPThumb2PostEncoder(MI, Binary);
  }


  Binary |= II->getPredicate(&MI) << ARMII::CondShift;

  emitWordLE(Binary);
}
