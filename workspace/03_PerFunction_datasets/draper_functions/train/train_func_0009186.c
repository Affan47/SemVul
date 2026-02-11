VisitCallPoint(MachineBasicBlock::iterator CI) {


  MachineBasicBlock::iterator RAI = CI;
  ++RAI;

  if (FI->getStrategy().needsSafePoint(GC::PreCall)) {
    MCSymbol *Label = InsertLabel(*CI->getParent(), CI, CI->getDebugLoc());
    FI->addSafePoint(GC::PreCall, Label, CI->getDebugLoc());
  }

  if (FI->getStrategy().needsSafePoint(GC::PostCall)) {
    MCSymbol *Label = InsertLabel(*CI->getParent(), RAI, CI->getDebugLoc());
    FI->addSafePoint(GC::PostCall, Label, CI->getDebugLoc());
  }
}
