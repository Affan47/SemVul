canVectorizeInst(Instruction *Inst, User *User) {
  switch (Inst->getOpcode()) {
  case Instruction::Load:
  case Instruction::BitCast:
  case Instruction::AddrSpaceCast:
    return true;
  case Instruction::Store: {

    StoreInst *SI = cast<StoreInst>(Inst);
    return SI->getPointerOperand() == User;
  }
  default:
    return false;
  }
}
