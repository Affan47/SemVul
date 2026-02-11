getConstantAt(Value *V, Instruction *At) {
  if (Constant *C = LVI->getConstant(V, At->getParent(), At))
    return C;


  auto *C = dyn_cast<CmpInst>(V);
  if (!C) return nullptr;

  Value *Op0 = C->getOperand(0);
  Constant *Op1 = dyn_cast<Constant>(C->getOperand(1));
  if (!Op1) return nullptr;

  LazyValueInfo::Tristate Result =
    LVI->getPredicateAt(C->getPredicate(), Op0, Op1, At);
  if (Result == LazyValueInfo::Unknown)
    return nullptr;

  return (Result == LazyValueInfo::True) ?
    ConstantInt::getTrue(C->getContext()) :
    ConstantInt::getFalse(C->getContext());
}
