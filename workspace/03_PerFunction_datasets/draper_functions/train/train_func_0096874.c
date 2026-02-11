StripDebugInfo(Module &M) {
  bool Changed = false;


  if (Function *Declare = M.getFunction("llvm.dbg.declare")) {
    while (!Declare->use_empty()) {
      CallInst *CI = cast<CallInst>(Declare->user_back());
      CI->eraseFromParent();
    }
    Declare->eraseFromParent();
    Changed = true;
  }

  if (Function *DbgVal = M.getFunction("llvm.dbg.value")) {
    while (!DbgVal->use_empty()) {
      CallInst *CI = cast<CallInst>(DbgVal->user_back());
      CI->eraseFromParent();
    }
    DbgVal->eraseFromParent();
    Changed = true;
  }

  for (Module::named_metadata_iterator NMI = M.named_metadata_begin(),
         NME = M.named_metadata_end(); NMI != NME;) {
    NamedMDNode *NMD = &*NMI;
    ++NMI;
    if (NMD->getName().startswith("llvm.dbg.")) {
      NMD->eraseFromParent();
      Changed = true;
    }
  }

  for (Function &F : M)
    Changed |= stripDebugInfo(F);

  if (GVMaterializer *Materializer = M.getMaterializer())
    Materializer->setStripDebugInfo();

  return Changed;
}
