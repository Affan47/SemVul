calculateAnticAvail(MachineFunction &Fn) {

  clearAnticAvailSets();


  bool changed = true;
  unsigned iterations = 0;
  while (changed) {
    changed = false;
    ++iterations;
    for (MachineFunction::iterator MBBI = Fn.begin(), MBBE = Fn.end();
         MBBI != MBBE; ++MBBI) {
      MachineBasicBlock* MBB = MBBI;


      changed |= calcAnticInOut(MBB);


      changed |= calcAvailInOut(MBB);
    }
  }

  DEBUG({
      if (ShrinkWrapDebugging >= Details) {
        dbgs()
          << "-----------------------------------------------------------\n"
          << " Antic/Avail Sets:\n"
          << "-----------------------------------------------------------\n"
          << "iterations = " << iterations << "\n"
          << "-----------------------------------------------------------\n"
          << "MBB | USED | ANTIC_IN | ANTIC_OUT | AVAIL_IN | AVAIL_OUT\n"
          << "-----------------------------------------------------------\n";

        for (MachineFunction::iterator MBBI = Fn.begin(), MBBE = Fn.end();
             MBBI != MBBE; ++MBBI) {
          MachineBasicBlock* MBB = MBBI;
          dumpSets(MBB);
        }

        dbgs()
          << "-----------------------------------------------------------\n";
      }
    });
}
