CanPHITrans(Instruction *Inst) {
  if (isa<PHINode>(Inst) ||
      isa<GetElementPtrInst>(Inst))
    return true;

  if (isa<CastInst>(Inst) &&
      isSafeToSpeculativelyExecute(Inst))
    return true;

  if (Inst->getOpcode() == Instruction::Add &&
      isa<ConstantInt>(Inst->getOperand(1)))
    return true;


  return false;
}
