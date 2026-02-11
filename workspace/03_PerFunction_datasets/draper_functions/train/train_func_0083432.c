placeSpillsAndRestores(MachineFunction &Fn) {
  CSRegBlockMap prevCSRSave;
  CSRegBlockMap prevCSRRestore;
  SmallVector<MachineBasicBlock*, 4> cvBlocks, ncvBlocks;
  bool changed = true;
  unsigned iterations = 0;


  while (changed) {
    changed = false;
    ++iterations;

    DEBUG(if (ShrinkWrapDebugging >= Iterations)
            dbgs() << "iter " << iterations
                 << " --------------------------------------------------\n");


    bool SRChanged = false;
    for (MachineFunction::iterator MBBI = Fn.begin(), MBBE = Fn.end();
         MBBI != MBBE; ++MBBI) {
      MachineBasicBlock* MBB = MBBI;


      SRChanged |= calcSpillPlacements(MBB, cvBlocks, prevCSRSave);


      SRChanged |= calcRestorePlacements(MBB, cvBlocks, prevCSRRestore);
    }


    changed |= addUsesForTopLevelLoops(cvBlocks);


    if (changed || SRChanged) {
      while (! cvBlocks.empty()) {
        MachineBasicBlock* MBB = cvBlocks.pop_back_val();
        changed |= addUsesForMEMERegion(MBB, ncvBlocks);
      }
      if (! ncvBlocks.empty()) {
        cvBlocks = ncvBlocks;
        ncvBlocks.clear();
      }
    }

    if (changed) {
      calculateAnticAvail(Fn);
      CSRSave.clear();
      CSRRestore.clear();
    }
  }


  CSRegSet notSpilledInEntryBlock = (UsedCSRegs - CSRSave[EntryBlock]);
  unsigned numSRReducedThisFunc = notSpilledInEntryBlock.count();
  numSRReduced += numSRReducedThisFunc;
  DEBUG(if (ShrinkWrapDebugging >= BasicInfo) {
      dbgs() << "-----------------------------------------------------------\n";
      dbgs() << "total iterations = " << iterations << " ( "
           << Fn.getFunction()->getName()
           << " " << numSRReducedThisFunc
           << " " << Fn.size()
           << " )\n";
      dbgs() << "-----------------------------------------------------------\n";
      dumpSRSets();
      dbgs() << "-----------------------------------------------------------\n";
      if (numSRReducedThisFunc)
        verifySpillRestorePlacement();
    });
}
