eliminateIVUser(Instruction *UseInst,
                                     Instruction *IVOperand) {
  if (ICmpInst *ICmp = dyn_cast<ICmpInst>(UseInst)) {
    eliminateIVComparison(ICmp, IVOperand);
    return true;
  }
  if (BinaryOperator *Rem = dyn_cast<BinaryOperator>(UseInst)) {
    bool IsSigned = Rem->getOpcode() == Instruction::SRem;
    if (IsSigned || Rem->getOpcode() == Instruction::URem) {
      eliminateIVRemainder(Rem, IVOperand, IsSigned);
      return true;
    }
  }

  if (eliminateIdentitySCEV(UseInst, IVOperand))
    return true;

  return false;
}
