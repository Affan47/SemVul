createDeadDef(SlotIndex Def,
                                  VNInfo::Allocator &VNInfoAllocator) {

  if (segmentSet != nullptr)
    return CalcLiveRangeUtilSet(this).createDeadDef(Def, VNInfoAllocator);

  return CalcLiveRangeUtilVector(this).createDeadDef(Def, VNInfoAllocator);
}
