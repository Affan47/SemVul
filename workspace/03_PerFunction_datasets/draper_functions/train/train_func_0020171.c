visitVAArgInst(VAArgInst &I) {
  ExecutionContext &SF = ECStack.back();


  GenericValue VAList = getOperandValue(I.getOperand(0), SF);
  GenericValue Dest;
  GenericValue Src = ECStack[VAList.UIntPairVal.first]
                      .VarArgs[VAList.UIntPairVal.second];
  Type *Ty = I.getType();
  switch (Ty->getTypeID()) {
  case Type::IntegerTyID:
    Dest.IntVal = Src.IntVal;
    break;
  IMPLEMENT_VAARG(Pointer);
  IMPLEMENT_VAARG(Float);
  IMPLEMENT_VAARG(Double);
  default:
    dbgs() << "Unhandled dest type for vaarg instruction: " << *Ty << "\n";
    llvm_unreachable(nullptr);
  }


  SetValue(&I, Dest, SF);


  ++VAList.UIntPairVal.second;
}
