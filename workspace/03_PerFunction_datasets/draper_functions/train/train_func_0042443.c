doInitialization(Module &Mod) {
  M = &Mod;
  const DataLayout &DL = Mod.getDataLayout();

  Triple TargetTriple(M->getTargetTriple());
  LinkerSubsectionsViaSymbols = TargetTriple.isMacOSX();
  Arch = TargetTriple.getArch();
  ObjectFormat = TargetTriple.getObjectFormat();

  Int1Ty = Type::getInt1Ty(M->getContext());
  Int8Ty = Type::getInt8Ty(M->getContext());
  Int32Ty = Type::getInt32Ty(M->getContext());
  Int32PtrTy = PointerType::getUnqual(Int32Ty);
  Int64Ty = Type::getInt64Ty(M->getContext());
  IntPtrTy = DL.getIntPtrType(M->getContext(), 0);

  BitSetNM = M->getNamedMetadata("llvm.bitsets");

  BitSetTestCallSites.clear();

  return false;
}
