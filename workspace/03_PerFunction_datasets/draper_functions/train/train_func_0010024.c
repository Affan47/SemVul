extendInBlock(SlotIndex StartIdx, SlotIndex Kill) {

  if (segmentSet != nullptr)
    return CalcLiveRangeUtilSet(this).extendInBlock(StartIdx, Kill);

  return CalcLiveRangeUtilVector(this).extendInBlock(StartIdx, Kill);
}
