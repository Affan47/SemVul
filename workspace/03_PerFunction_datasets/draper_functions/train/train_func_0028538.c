getExtractElementTy(const Type *ReqTy, Constant *Val,
                                            Constant *Idx) {
  if (Constant *FC = ConstantFoldExtractElementInstruction(Val, Idx))
    return FC;

  std::vector<Constant*> ArgVec(1, Val);
  ArgVec.push_back(Idx);
  const ExprMapKeyType Key(Instruction::ExtractElement,ArgVec);

  LLVMContextImpl *pImpl = ReqTy->getContext().pImpl;
  return pImpl->ExprConstants.getOrCreate(ReqTy, Key);
}
