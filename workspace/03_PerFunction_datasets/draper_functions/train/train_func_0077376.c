CreateMem(unsigned BaseRegNum,
                               const MCConstantExpr *OffsetImm,
                               unsigned OffsetRegNum,
                               ARM_AM::ShiftOpc ShiftType,
                               unsigned ShiftImm,
                               unsigned Alignment,
                               bool isNegative,
                               SMLoc S, SMLoc E) {
    ARMOperand *Op = new ARMOperand(k_Memory);
    Op->Memory.BaseRegNum = BaseRegNum;
    Op->Memory.OffsetImm = OffsetImm;
    Op->Memory.OffsetRegNum = OffsetRegNum;
    Op->Memory.ShiftType = ShiftType;
    Op->Memory.ShiftImm = ShiftImm;
    Op->Memory.Alignment = Alignment;
    Op->Memory.isNegative = isNegative;
    Op->StartLoc = S;
    Op->EndLoc = E;
    return Op;
  }
