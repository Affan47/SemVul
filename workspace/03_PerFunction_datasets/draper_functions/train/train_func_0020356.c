poisonOneInitializer(Function &GlobalInit,
                                                  GlobalValue *ModuleName) {

  IRBuilder<> IRB(&GlobalInit.front(),
                  GlobalInit.front().getFirstInsertionPt());


  Value *ModuleNameAddr = ConstantExpr::getPointerCast(ModuleName, IntptrTy);
  IRB.CreateCall(AsanPoisonGlobals, ModuleNameAddr);


  for (auto &BB : GlobalInit.getBasicBlockList())
    if (ReturnInst *RI = dyn_cast<ReturnInst>(BB.getTerminator()))
      CallInst::Create(AsanUnpoisonGlobals, "", RI);
}
