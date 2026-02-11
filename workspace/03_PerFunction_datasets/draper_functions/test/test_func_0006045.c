FindUsedValues(GlobalVariable *LLVMUsed,
                           SmallPtrSetImpl<const GlobalValue*> &UsedValues) {
  if (!LLVMUsed) return;
  ConstantArray *Inits = cast<ConstantArray>(LLVMUsed->getInitializer());

  for (unsigned i = 0, e = Inits->getNumOperands(); i != e; ++i) {
    Value *Operand = Inits->getOperand(i)->stripPointerCastsNoFollowAliases();
    GlobalValue *GV = cast<GlobalValue>(Operand);
    UsedValues.insert(GV);
  }
}
