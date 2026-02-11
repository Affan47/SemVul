WaterIsInRange(unsigned UserOffset,
                                        MachineBasicBlock* Water, CPUser &U) {
  unsigned MaxDisp = U.MaxDisp;
  unsigned CPEOffset = BBOffsets[Water->getNumber()] +
                       BBSizes[Water->getNumber()];


  if (CPEOffset < UserOffset)
    UserOffset += U.CPEMI->getOperand(2).getImm();

  return OffsetIsInRange(UserOffset, CPEOffset, MaxDisp, U.NegOk, U.IsSoImm);
}
