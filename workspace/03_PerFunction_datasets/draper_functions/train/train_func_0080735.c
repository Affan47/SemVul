runOnModule(Module &M) {
  CallGraph *CG = getAnalysisIfAvailable<CallGraph>();
  CallGraphNode *ExternalNode = CG ? CG->getExternalCallingNode() : 0;

  if (ExternalNames.empty()) {

    if (!AllButMain)
      return false;


    Function *MainFunc = M.getFunction("main");
    if (MainFunc == 0 || MainFunc->isDeclaration())
      return false;


    ExternalNames.insert(MainFunc->getName());
  }

  bool Changed = false;


  for (Module::iterator I = M.begin(), E = M.end(); I != E; ++I)
    if (!I->isDeclaration() &&

        !I->hasAvailableExternallyLinkage() &&
        !I->hasLocalLinkage() &&
        !ExternalNames.count(I->getName())) {
      I->setLinkage(GlobalValue::InternalLinkage);

      if (ExternalNode) ExternalNode->removeOneAbstractEdgeTo((*CG)[I]);
      Changed = true;
      ++NumFunctions;
      DEBUG(dbgs() << "Internalizing func " << I->getName() << "\n");
    }


  ExternalNames.insert("llvm.used");
  ExternalNames.insert("llvm.compiler.used");


  ExternalNames.insert("llvm.global_ctors");
  ExternalNames.insert("llvm.global_dtors");
  ExternalNames.insert("llvm.noinline");
  ExternalNames.insert("llvm.global.annotations");


  for (Module::global_iterator I = M.global_begin(), E = M.global_end();
       I != E; ++I)
    if (!I->isDeclaration() && !I->hasLocalLinkage() &&

        !I->hasAvailableExternallyLinkage() &&
        !ExternalNames.count(I->getName())) {
      I->setLinkage(GlobalValue::InternalLinkage);
      Changed = true;
      ++NumGlobals;
      DEBUG(dbgs() << "Internalized gvar " << I->getName() << "\n");
    }


  for (Module::alias_iterator I = M.alias_begin(), E = M.alias_end();
       I != E; ++I)
    if (!I->isDeclaration() && !I->hasInternalLinkage() &&

        !I->hasAvailableExternallyLinkage() &&
        !ExternalNames.count(I->getName())) {
      I->setLinkage(GlobalValue::InternalLinkage);
      Changed = true;
      ++NumAliases;
      DEBUG(dbgs() << "Internalized alias " << I->getName() << "\n");
    }

  return Changed;
}
