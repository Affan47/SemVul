CastGEPIndices(Type *SrcTy, ArrayRef<Constant *> Ops,
                                Type *ResultTy, const DataLayout &DL,
                                const TargetLibraryInfo *TLI) {
  Type *IntPtrTy = DL.getIntPtrType(ResultTy);

  bool Any = false;
  SmallVector<Constant*, 32> NewIdxs;
  for (unsigned i = 1, e = Ops.size(); i != e; ++i) {
    if ((i == 1 ||
         !isa<StructType>(GetElementPtrInst::getIndexedType(
             cast<PointerType>(Ops[0]->getType()->getScalarType())
                 ->getElementType(),
             Ops.slice(1, i - 1)))) &&
        Ops[i]->getType() != IntPtrTy) {
      Any = true;
      NewIdxs.push_back(ConstantExpr::getCast(CastInst::getCastOpcode(Ops[i],
                                                                      true,
                                                                      IntPtrTy,
                                                                      true),
                                              Ops[i], IntPtrTy));
    } else
      NewIdxs.push_back(Ops[i]);
  }

  if (!Any)
    return nullptr;

  Constant *C = ConstantExpr::getGetElementPtr(SrcTy, Ops[0], NewIdxs);
  if (ConstantExpr *CE = dyn_cast<ConstantExpr>(C)) {
    if (Constant *Folded = ConstantFoldConstantExpression(CE, DL, TLI))
      C = Folded;
  }

  return C;
}
