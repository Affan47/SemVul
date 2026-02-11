ComputeLoadResult(Constant *P,
                                const DenseMap<Constant*, Constant*> &Memory) {


  DenseMap<Constant*, Constant*>::const_iterator I = Memory.find(P);
  if (I != Memory.end()) return I->second;


  if (GlobalVariable *GV = dyn_cast<GlobalVariable>(P)) {
    if (GV->hasDefinitiveInitializer())
      return GV->getInitializer();
    return 0;
  }


  if (ConstantExpr *CE = dyn_cast<ConstantExpr>(P))
    if (CE->getOpcode() == Instruction::GetElementPtr &&
        isa<GlobalVariable>(CE->getOperand(0))) {
      GlobalVariable *GV = cast<GlobalVariable>(CE->getOperand(0));
      if (GV->hasDefinitiveInitializer())
        return ConstantFoldLoadThroughGEPConstantExpr(GV->getInitializer(), CE);
    }

  return 0;
}
