EmitMemChr(Value *Ptr, Value *Val, Value *Len, IRBuilder<> &B,
                        const DataLayout &DL, const TargetLibraryInfo *TLI) {
  if (!TLI->has(LibFunc::memchr))
    return nullptr;

  Module *M = B.GetInsertBlock()->getParent()->getParent();
  AttributeSet AS;
  Attribute::AttrKind AVs[2] = { Attribute::ReadOnly, Attribute::NoUnwind };
  AS = AttributeSet::get(M->getContext(), AttributeSet::FunctionIndex, AVs);
  LLVMContext &Context = B.GetInsertBlock()->getContext();
  Value *MemChr = M->getOrInsertFunction(
      "memchr", AttributeSet::get(M->getContext(), AS), B.getInt8PtrTy(),
      B.getInt8PtrTy(), B.getInt32Ty(), DL.getIntPtrType(Context), nullptr);
  CallInst *CI = B.CreateCall(MemChr, {CastToCStr(Ptr, B), Val, Len}, "memchr");

  if (const Function *F = dyn_cast<Function>(MemChr->stripPointerCasts()))
    CI->setCallingConv(F->getCallingConv());

  return CI;
}
