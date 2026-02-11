isSimpleIndexCalc(MachineInstr &I, unsigned EntryReg,
                              unsigned BaseReg) {
  if (I.getOpcode() != ARM::t2ADDrs)
    return false;

  if (I.getOperand(0).getReg() != EntryReg)
    return false;

  if (I.getOperand(1).getReg() != BaseReg)
    return false;


  return true;
}
