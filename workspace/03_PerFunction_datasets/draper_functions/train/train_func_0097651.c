LowerDbgDeclare(Function &F) {
  DIBuilder DIB(*F.getParent(),  false);
  SmallVector<DbgDeclareInst *, 4> Dbgs;
  for (auto &FI : F)
    for (Instruction &BI : FI)
      if (auto DDI = dyn_cast<DbgDeclareInst>(&BI))
        Dbgs.push_back(DDI);

  if (Dbgs.empty())
    return false;

  for (auto &I : Dbgs) {
    DbgDeclareInst *DDI = I;
    AllocaInst *AI = dyn_cast_or_null<AllocaInst>(DDI->getAddress());


    if (AI && !isArray(AI)) {
      for (User *U : AI->users())
        if (StoreInst *SI = dyn_cast<StoreInst>(U))
          ConvertDebugDeclareToDebugValue(DDI, SI, DIB);
        else if (LoadInst *LI = dyn_cast<LoadInst>(U))
          ConvertDebugDeclareToDebugValue(DDI, LI, DIB);
        else if (CallInst *CI = dyn_cast<CallInst>(U)) {


          DIB.insertDbgValueIntrinsic(AI, 0, DDI->getVariable(),
                                      DDI->getExpression(), DDI->getDebugLoc(),
                                      CI);
        }
      DDI->eraseFromParent();
    }
  }
  return true;
}
