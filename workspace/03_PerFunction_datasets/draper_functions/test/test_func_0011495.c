GetFrameMap(Function &F) {

  Type *VoidPtr = Type::getInt8PtrTy(F.getContext());


  unsigned NumMeta = 0;
  SmallVector<Constant *, 16> Metadata;
  for (unsigned I = 0; I != Roots.size(); ++I) {
    Constant *C = cast<Constant>(Roots[I].first->getArgOperand(1));
    if (!C->isNullValue())
      NumMeta = I + 1;
    Metadata.push_back(ConstantExpr::getBitCast(C, VoidPtr));
  }
  Metadata.resize(NumMeta);

  Type *Int32Ty = Type::getInt32Ty(F.getContext());

  Constant *BaseElts[] = {
      ConstantInt::get(Int32Ty, Roots.size(), false),
      ConstantInt::get(Int32Ty, NumMeta, false),
  };

  Constant *DescriptorElts[] = {
      ConstantStruct::get(FrameMapTy, BaseElts),
      ConstantArray::get(ArrayType::get(VoidPtr, NumMeta), Metadata)};

  Type *EltTys[] = {DescriptorElts[0]->getType(), DescriptorElts[1]->getType()};
  StructType *STy = StructType::create(EltTys, "gc_map." + utostr(NumMeta));

  Constant *FrameMap = ConstantStruct::get(STy, DescriptorElts);


  Constant *GV = new GlobalVariable(*F.getParent(), FrameMap->getType(), true,
                                    GlobalVariable::InternalLinkage, FrameMap,
                                    "__gc_" + F.getName());

  Constant *GEPIndices[2] = {
      ConstantInt::get(Type::getInt32Ty(F.getContext()), 0),
      ConstantInt::get(Type::getInt32Ty(F.getContext()), 0)};
  return ConstantExpr::getGetElementPtr(FrameMap->getType(), GV, GEPIndices);
}
