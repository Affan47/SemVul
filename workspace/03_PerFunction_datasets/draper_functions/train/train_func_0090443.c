split() {
  splitAnalysis_.analyze(li_);

  if (const MachineLoop *loop = splitAnalysis_.getBestSplitLoop()) {

    if (SplitEditor(splitAnalysis_, lis_, vrm_, *newIntervals_)
          .splitAroundLoop(loop))
      return true;
  }


  SplitAnalysis::BlockPtrSet blocks;
  if (splitAnalysis_.getMultiUseBlocks(blocks)) {
    if (SplitEditor(splitAnalysis_, lis_, vrm_, *newIntervals_)
          .splitSingleBlocks(blocks))
      return true;
  }


  if (const MachineBasicBlock *MBB = splitAnalysis_.getBlockForInsideSplit()) {
    if (SplitEditor(splitAnalysis_, lis_, vrm_, *newIntervals_)
          .splitInsideBlock(MBB))
      return true;
  }


  return false;
}
