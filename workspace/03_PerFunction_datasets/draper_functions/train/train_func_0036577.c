StartMachineBasicBlock(MachineBasicBlock *MBB) {
      if (MBBLocations.size() <= (unsigned)MBB->getNumber())
        MBBLocations.resize((MBB->getNumber()+1)*2);
      MBBLocations[MBB->getNumber()] = getCurrentPCValue();
      if (MBB->hasAddressTaken())
        TheJIT->addPointerToBasicBlock(MBB->getBasicBlock(),
                                       (void*)getCurrentPCValue());
      DEBUG(dbgs() << "JIT: Emitting BB" << MBB->getNumber() << " at ["
                   << (void*) getCurrentPCValue() << "]\n");
    }
