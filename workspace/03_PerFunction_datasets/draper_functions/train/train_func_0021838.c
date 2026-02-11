verifyCTRBranch(MachineBasicBlock *MBB,
                            MachineBasicBlock::iterator I) {
  MachineBasicBlock::iterator BI = I;
  SmallSet<MachineBasicBlock *, 16>   Visited;
  SmallVector<MachineBasicBlock *, 8> Preds;
  bool CheckPreds;

  if (I == MBB->begin()) {
    Visited.insert(MBB);
    goto queue_preds;
  } else
    --I;

check_block:
  Visited.insert(MBB);
  if (I == MBB->end())
    goto queue_preds;

  CheckPreds = true;
  for (MachineBasicBlock::iterator IE = MBB->begin();; --I) {
    unsigned Opc = I->getOpcode();
    if (Opc == PPC::MTCTRloop || Opc == PPC::MTCTR8loop) {
      CheckPreds = false;
      break;
    }

    if (I != BI && clobbersCTR(I)) {
      DEBUG(dbgs() << "BB#" << MBB->getNumber() << " (" <<
                      MBB->getFullName() << ") instruction " << *I <<
                      " clobbers CTR, invalidating " << "BB#" <<
                      BI->getParent()->getNumber() << " (" <<
                      BI->getParent()->getFullName() << ") instruction " <<
                      *BI << "\n");
      return false;
    }

    if (I == IE)
      break;
  }

  if (!CheckPreds && Preds.empty())
    return true;

  if (CheckPreds) {
queue_preds:
    if (MachineFunction::iterator(MBB) == MBB->getParent()->begin()) {
      DEBUG(dbgs() << "Unable to find a MTCTR instruction for BB#" <<
                      BI->getParent()->getNumber() << " (" <<
                      BI->getParent()->getFullName() << ") instruction " <<
                      *BI << "\n");
      return false;
    }

    for (MachineBasicBlock::pred_iterator PI = MBB->pred_begin(),
         PIE = MBB->pred_end(); PI != PIE; ++PI)
      Preds.push_back(*PI);
  }

  do {
    MBB = Preds.pop_back_val();
    if (!Visited.count(MBB)) {
      I = MBB->getLastNonDebugInstr();
      goto check_block;
    }
  } while (!Preds.empty());

  return true;
}
