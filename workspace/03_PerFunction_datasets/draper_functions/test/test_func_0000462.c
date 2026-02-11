ProcessGlobal(GlobalVariable *GV,
                              Module::global_iterator &GVI) {

  GV->removeDeadConstantUsers();

  if (GV->use_empty()) {
    DEBUG(dbgs() << "GLOBAL DEAD: " << *GV << "\n");
    GV->eraseFromParent();
    ++NumDeleted;
    return true;
  }

  if (!GV->hasLocalLinkage())
    return false;

  GlobalStatus GS;

  if (GlobalStatus::analyzeGlobal(GV, GS))
    return false;

  if (!GS.IsCompared && !GV->hasUnnamedAddr()) {
    GV->setUnnamedAddr(true);
    NumUnnamed++;
  }

  if (GV->isConstant() || !GV->hasInitializer())
    return false;

  return ProcessInternalGlobal(GV, GVI, GS);
}
