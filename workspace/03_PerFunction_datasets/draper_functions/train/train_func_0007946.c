insertCallSiteStore(Instruction *I, int Number,
                                     Value *CallSite) {
  ConstantInt *CallSiteNoC = ConstantInt::get(Type::getInt32Ty(I->getContext()),
                                              Number);

  new StoreInst(CallSiteNoC, CallSite, true, I);
}
