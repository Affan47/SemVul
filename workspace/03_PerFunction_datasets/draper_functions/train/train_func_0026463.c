RewriteBitCast(BitCastInst *BC, AllocaInst *AI, uint64_t Offset,
                          SmallVectorImpl<AllocaInst *> &NewElts) {
  RewriteForScalarRepl(BC, AI, Offset, NewElts);
  if (BC->getOperand(0) != AI)
    return;


  Type *T = AI->getAllocatedType();
  uint64_t EltOffset = 0;
  Type *IdxTy;
  uint64_t Idx = FindElementAndOffset(T, EltOffset, IdxTy,
                                      BC->getModule()->getDataLayout());
  Instruction *Val = NewElts[Idx];
  if (Val->getType() != BC->getDestTy()) {
    Val = new BitCastInst(Val, BC->getDestTy(), "", BC);
    Val->takeName(BC);
  }
  BC->replaceAllUsesWith(Val);
  DeadInsts.push_back(BC);
}
