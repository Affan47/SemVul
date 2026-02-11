spill(LiveInterval *li,
             SmallVectorImpl<LiveInterval*> &newIntervals,
             SmallVectorImpl<LiveInterval*> &spillIs) {
    if (worthTryingToSplit(li))
      tryVNISplit(li);
    else
      StandardSpiller::spill(li, newIntervals, spillIs);
  }
