OptimizeGlobalVars(Module &M) {
  bool Changed = false;
  for (Module::global_iterator GVI = M.global_begin(), E = M.global_end();
       GVI != E; ) {
    GlobalVariable *GV = GVI++;

    if (!GV->hasName() && !GV->isDeclaration())
      GV->setLinkage(GlobalValue::InternalLinkage);

    if (GV->hasInitializer())
      if (ConstantExpr *CE = dyn_cast<ConstantExpr>(GV->getInitializer())) {
        TargetData *TD = getAnalysisIfAvailable<TargetData>();
        Constant *New = ConstantFoldConstantExpression(CE, TD);
        if (New && New != CE)
          GV->setInitializer(New);
      }

    Changed |= ProcessGlobal(GV, GVI);
  }
  return Changed;
}
