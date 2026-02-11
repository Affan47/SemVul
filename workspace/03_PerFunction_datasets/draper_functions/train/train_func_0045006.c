AnalyzeLoadFromClobberingMemInst(Type *LoadTy, Value *LoadPtr,
                                            MemIntrinsic *MI,
                                            const DataLayout &DL) {

  ConstantInt *SizeCst = dyn_cast<ConstantInt>(MI->getLength());
  if (!SizeCst) return -1;
  uint64_t MemSizeInBits = SizeCst->getZExtValue()*8;


  if (MI->getIntrinsicID() == Intrinsic::memset)
    return AnalyzeLoadFromClobberingWrite(LoadTy, LoadPtr, MI->getDest(),
                                          MemSizeInBits, DL);


  MemTransferInst *MTI = cast<MemTransferInst>(MI);

  Constant *Src = dyn_cast<Constant>(MTI->getSource());
  if (!Src) return -1;

  GlobalVariable *GV = dyn_cast<GlobalVariable>(GetUnderlyingObject(Src, DL));
  if (!GV || !GV->isConstant()) return -1;


  int Offset = AnalyzeLoadFromClobberingWrite(LoadTy, LoadPtr,
                                              MI->getDest(), MemSizeInBits, DL);
  if (Offset == -1)
    return Offset;

  unsigned AS = Src->getType()->getPointerAddressSpace();


  Src = ConstantExpr::getBitCast(Src,
                                 Type::getInt8PtrTy(Src->getContext(), AS));
  Constant *OffsetCst =
    ConstantInt::get(Type::getInt64Ty(Src->getContext()), (unsigned)Offset);
  Src = ConstantExpr::getGetElementPtr(Type::getInt8Ty(Src->getContext()), Src,
                                       OffsetCst);
  Src = ConstantExpr::getBitCast(Src, PointerType::get(LoadTy, AS));
  if (ConstantFoldLoadFromConstPtr(Src, DL))
    return Offset;
  return -1;
}
