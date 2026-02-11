findFastExitPath() {
  if (! EntryBlock)
    return;


  for (MachineBasicBlock::succ_iterator SI = EntryBlock->succ_begin(),
         SE = EntryBlock->succ_end(); SI != SE; ++SI) {
    MachineBasicBlock* SUCC = *SI;


    HasFastExitPath = true;


    if (isReturnBlock(SUCC)) {
      if (ShrinkWrapDebugging >= BasicInfo)
        dbgs() << "Fast exit path: " << getBasicBlockName(EntryBlock)
             << "->" << getBasicBlockName(SUCC) << "\n";
      break;
    }

    std::string exitPath = getBasicBlockName(SUCC);
    for (df_iterator<MachineBasicBlock*> BI = df_begin(SUCC),
           BE = df_end(SUCC); BI != BE; ++BI) {
      MachineBasicBlock* SBB = *BI;

      if (SBB->succ_size() > 1) {
        HasFastExitPath = false;
        break;
      }
      exitPath += "->" + getBasicBlockName(SBB);
    }
    if (HasFastExitPath) {
      if (ShrinkWrapDebugging >= BasicInfo)
        dbgs() << "Fast exit path: " << getBasicBlockName(EntryBlock)
             << "->" << exitPath << "\n";
      break;
    }
  }
}
