get(Type *ReturnType,
                                ArrayRef<Type*> Params, bool isVarArg) {

  std::vector<Type*> Key;
  Key.reserve(Params.size()+2);
  Key.push_back(const_cast<Type*>(ReturnType));
  for (unsigned i = 0, e = Params.size(); i != e; ++i)
    Key.push_back(const_cast<Type*>(Params[i]));
  if (isVarArg)
    Key.push_back(0);

  LLVMContextImpl *pImpl = ReturnType->getContext().pImpl;
  FunctionType *&FT = pImpl->FunctionTypes[Key];

  if (FT == 0) {
    FT = (FunctionType*) pImpl->TypeAllocator.
      Allocate(sizeof(FunctionType) + sizeof(Type*)*(Params.size()+1),
               AlignOf<FunctionType>::Alignment);
    new (FT) FunctionType(ReturnType, Params, isVarArg);
  }

  return FT;
}
