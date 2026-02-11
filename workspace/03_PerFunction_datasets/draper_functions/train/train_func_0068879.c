runOnModule(Module &M) {
  CallGraphWrapperPass *CGPass = getAnalysisIfAvailable<CallGraphWrapperPass>();
  CallGraph *CG = CGPass ? &CGPass->getCallGraph() : nullptr;
  CallGraphNode *ExternalNode = CG ? CG->getExternalCallingNode() : nullptr;

  SmallPtrSet<GlobalValue *, 8> Used;
  collectUsedGlobalVariables(M, Used, false);


  std::set<const Comdat *> ExternalComdats;
  if (!M.getComdatSymbolTable().empty()) {
    for (Function &F : M)
      checkComdatVisibility(F, ExternalComdats);
    for (GlobalVariable &GV : M.globals())
      checkComdatVisibility(GV, ExternalComdats);
    for (GlobalAlias &GA : M.aliases())
      checkComdatVisibility(GA, ExternalComdats);
  }


  for (GlobalValue *V : Used) {
    ExternalNames.insert(V->getName());
  }


  for (Function &I : M) {
    if (!maybeInternalize(I, ExternalComdats))
      continue;

    if (ExternalNode)

      ExternalNode->removeOneAbstractEdgeTo((*CG)[&I]);

    ++NumFunctions;
    DEBUG(dbgs() << "Internalizing func " << I.getName() << "\n");
  }


  ExternalNames.insert("llvm.used");
  ExternalNames.insert("llvm.compiler.used");


  ExternalNames.insert("llvm.global_ctors");
  ExternalNames.insert("llvm.global_dtors");
  ExternalNames.insert("llvm.global.annotations");


  ExternalNames.insert("__stack_chk_fail");
  ExternalNames.insert("__stack_chk_guard");


  for (Module::global_iterator I = M.global_begin(), E = M.global_end();
       I != E; ++I) {
    if (!maybeInternalize(*I, ExternalComdats))
      continue;

    ++NumGlobals;
    DEBUG(dbgs() << "Internalized gvar " << I->getName() << "\n");
  }


  for (Module::alias_iterator I = M.alias_begin(), E = M.alias_end();
       I != E; ++I) {
    if (!maybeInternalize(*I, ExternalComdats))
      continue;

    ++NumAliases;
    DEBUG(dbgs() << "Internalized alias " << I->getName() << "\n");
  }


  return true;
}
