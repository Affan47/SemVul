ParseAtomicRMW(Instruction *&Inst, PerFunctionState &PFS) {
  Value *Ptr, *Val; LocTy PtrLoc, ValLoc;
  bool AteExtraComma = false;
  AtomicOrdering Ordering = NotAtomic;
  SynchronizationScope Scope = CrossThread;
  bool isVolatile = false;
  AtomicRMWInst::BinOp Operation;

  if (EatIfPresent(lltok::kw_volatile))
    isVolatile = true;

  switch (Lex.getKind()) {
  default: return TokError("expected binary operation in atomicrmw");
  case lltok::kw_xchg: Operation = AtomicRMWInst::Xchg; break;
  case lltok::kw_add: Operation = AtomicRMWInst::Add; break;
  case lltok::kw_sub: Operation = AtomicRMWInst::Sub; break;
  case lltok::kw_and: Operation = AtomicRMWInst::And; break;
  case lltok::kw_nand: Operation = AtomicRMWInst::Nand; break;
  case lltok::kw_or: Operation = AtomicRMWInst::Or; break;
  case lltok::kw_xor: Operation = AtomicRMWInst::Xor; break;
  case lltok::kw_max: Operation = AtomicRMWInst::Max; break;
  case lltok::kw_min: Operation = AtomicRMWInst::Min; break;
  case lltok::kw_umax: Operation = AtomicRMWInst::UMax; break;
  case lltok::kw_umin: Operation = AtomicRMWInst::UMin; break;
  }
  Lex.Lex();

  if (ParseTypeAndValue(Ptr, PtrLoc, PFS) ||
      ParseToken(lltok::comma, "expected ',' after atomicrmw address") ||
      ParseTypeAndValue(Val, ValLoc, PFS) ||
      ParseScopeAndOrdering(true , Scope, Ordering))
    return true;

  if (Ordering == Unordered)
    return TokError("atomicrmw cannot be unordered");
  if (!Ptr->getType()->isPointerTy())
    return Error(PtrLoc, "atomicrmw operand must be a pointer");
  if (cast<PointerType>(Ptr->getType())->getElementType() != Val->getType())
    return Error(ValLoc, "atomicrmw value and pointer type do not match");
  if (!Val->getType()->isIntegerTy())
    return Error(ValLoc, "atomicrmw operand must be an integer");
  unsigned Size = Val->getType()->getPrimitiveSizeInBits();
  if (Size < 8 || (Size & (Size - 1)))
    return Error(ValLoc, "atomicrmw operand must be power-of-two byte-sized"
                         " integer");

  AtomicRMWInst *RMWI =
    new AtomicRMWInst(Operation, Ptr, Val, Ordering, Scope);
  RMWI->setVolatile(isVolatile);
  Inst = RMWI;
  return AteExtraComma ? InstExtraComma : InstNormal;
}
