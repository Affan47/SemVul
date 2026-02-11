ConvertDebugDeclareToDebugValue(DbgDeclareInst *DDI,
                                                     StoreInst *SI) {
  DIVariable DIVar(DDI->getVariable());
  if (!DIVar.Verify())
    return;

  if (!DIF)
    DIF = new DIFactory(*SI->getParent()->getParent()->getParent());
  Instruction *DbgVal = DIF->InsertDbgValueIntrinsic(SI->getOperand(0), 0,
                                                     DIVar, SI);


  DebugLoc SIDL = SI->getDebugLoc();
  if (!SIDL.isUnknown())
    DbgVal->setDebugLoc(SIDL);

  else
    DbgVal->setDebugLoc(DDI->getDebugLoc());
}
