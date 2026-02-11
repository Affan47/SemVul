getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesCFG();
      MachineFunctionPass::getAnalysisUsage(AU);
      AU.addRequired<AAResultsWrapperPass>();
      AU.addRequired<MachineDominatorTree>();
      AU.addRequired<MachinePostDominatorTree>();
      AU.addRequired<MachineLoopInfo>();
      AU.addPreserved<MachineDominatorTree>();
      AU.addPreserved<MachinePostDominatorTree>();
      AU.addPreserved<MachineLoopInfo>();
      if (UseBlockFreqInfo)
        AU.addRequired<MachineBlockFrequencyInfo>();
    }
