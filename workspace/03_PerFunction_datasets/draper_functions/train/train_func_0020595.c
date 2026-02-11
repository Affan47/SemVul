selectInstruction(const Instruction *I) {


  if (isa<TerminatorInst>(I))
    if (!handlePHINodesInSuccessorBlocks(I->getParent()))
      return false;

  DbgLoc = I->getDebugLoc();

  SavedInsertPt = FuncInfo.InsertPt;

  if (const auto *Call = dyn_cast<CallInst>(I)) {
    const Function *F = Call->getCalledFunction();
    LibFunc::Func Func;


    if (F && !F->hasLocalLinkage() && F->hasName() &&
        LibInfo->getLibFunc(F->getName(), Func) &&
        LibInfo->hasOptimizedCodeGen(Func))
      return false;


    if (F && F->getIntrinsicID() == Intrinsic::trap &&
        Call->hasFnAttr("trap-func-name"))
      return false;
  }


  if (!SkipTargetIndependentISel) {
    if (selectOperator(I, I->getOpcode())) {
      ++NumFastIselSuccessIndependent;
      DbgLoc = DebugLoc();
      return true;
    }

    recomputeInsertPt();
    if (SavedInsertPt != FuncInfo.InsertPt)
      removeDeadCode(FuncInfo.InsertPt, SavedInsertPt);
    SavedInsertPt = FuncInfo.InsertPt;
  }

  if (fastSelectInstruction(I)) {
    ++NumFastIselSuccessTarget;
    DbgLoc = DebugLoc();
    return true;
  }

  recomputeInsertPt();
  if (SavedInsertPt != FuncInfo.InsertPt)
    removeDeadCode(FuncInfo.InsertPt, SavedInsertPt);

  DbgLoc = DebugLoc();

  if (isa<TerminatorInst>(I))
    FuncInfo.PHINodesToUpdate.resize(FuncInfo.OrigNumPHINodesToUpdate);
  return false;
}
