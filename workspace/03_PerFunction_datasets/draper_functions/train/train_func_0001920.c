ConstantFoldInsertElementInstruction(Constant *Val,
                                                     Constant *Elt,
                                                     Constant *Idx) {
  if (isa<UndefValue>(Idx))
    return UndefValue::get(Val->getType());

  ConstantInt *CIdx = dyn_cast<ConstantInt>(Idx);
  if (!CIdx) return nullptr;

  unsigned NumElts = Val->getType()->getVectorNumElements();
  if (CIdx->uge(NumElts))
    return UndefValue::get(Val->getType());

  SmallVector<Constant*, 16> Result;
  Result.reserve(NumElts);
  auto *Ty = Type::getInt32Ty(Val->getContext());
  uint64_t IdxVal = CIdx->getZExtValue();
  for (unsigned i = 0; i != NumElts; ++i) {
    if (i == IdxVal) {
      Result.push_back(Elt);
      continue;
    }

    Constant *C = ConstantExpr::getExtractElement(Val, ConstantInt::get(Ty, i));
    Result.push_back(C);
  }

  return ConstantVector::get(Result);
}
