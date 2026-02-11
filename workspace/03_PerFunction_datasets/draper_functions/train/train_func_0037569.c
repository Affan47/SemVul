processHeader(LoopSplit &split) {
    MachineBasicBlock &header = *split.getLoop().getHeader();


    if (!lis->isLiveInToMBB(split.getLI(), &header))
      return;

    MachineBasicBlock *preHeader = split.getLoop().getLoopPreheader();
    if (!preHeader) {

      if (!canInsertPreHeader(split.getLoop())) {
        split.invalidate();
        return;
      }

      for (MachineBasicBlock::pred_iterator predItr = header.pred_begin(),
                                            predEnd = header.pred_end();
           predItr != predEnd; ++predItr) {
        if (lis->isLiveOutOfMBB(split.getLI(), *predItr)) {
          split.splitIncoming();
          break;
        }
      }
    } else if (lis->isLiveOutOfMBB(split.getLI(), preHeader)) {
      split.splitIncoming();
    }
  }
