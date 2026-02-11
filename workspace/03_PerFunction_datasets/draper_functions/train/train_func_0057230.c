startNewBlock() {
  LocalValueMap.clear();

  EmitStartPt = 0;


  MachineBasicBlock::iterator
    I = FuncInfo.MBB->begin(), E = FuncInfo.MBB->end();
  while (I != E && I->getOpcode() == TargetOpcode::EH_LABEL) {
    EmitStartPt = I;
    ++I;
  }
  LastLocalValue = EmitStartPt;
}
