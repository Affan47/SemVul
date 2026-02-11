AdjustBBOffsetsAfter(MachineBasicBlock *BB,
                                              int delta) {
  MachineFunction::iterator MBBI = BB; MBBI = llvm::next(MBBI);
  for(unsigned i = BB->getNumber()+1, e = BB->getParent()->getNumBlockIDs();
      i < e; ++i) {
    BBOffsets[i] += delta;


    if (!isThumb)
      continue;
    MachineBasicBlock *MBB = MBBI;
    if (!MBB->empty() && !HasInlineAsm) {

      if (MBB->begin()->getOpcode() == ARM::CONSTPOOL_ENTRY) {
        unsigned OldOffset = BBOffsets[i] - delta;
        if ((OldOffset%4) == 0 && (BBOffsets[i]%4) != 0) {

          BBSizes[i] += 2;
          delta += 2;
        } else if ((OldOffset%4) != 0 && (BBOffsets[i]%4) == 0) {

          BBSizes[i] -= 2;
          delta -= 2;
        }
      }


      MachineInstr *ThumbJTMI = prior(MBB->end());
      if (ThumbJTMI->getOpcode() == ARM::tBR_JTr) {
        unsigned NewMIOffset = GetOffsetOf(ThumbJTMI);
        unsigned OldMIOffset = NewMIOffset - delta;
        if ((OldMIOffset%4) == 0 && (NewMIOffset%4) != 0) {

          BBSizes[i] -= 2;
          delta -= 2;
        } else if ((OldMIOffset%4) != 0 && (NewMIOffset%4) == 0) {

          BBSizes[i] += 2;
          delta += 2;
        }
      }
      if (delta==0)
        return;
    }
    MBBI = llvm::next(MBBI);
  }
}
