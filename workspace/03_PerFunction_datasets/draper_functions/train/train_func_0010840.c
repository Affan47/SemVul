isSafeAccess(ObjectSizeOffsetVisitor &ObjSizeVis,
                                    Value *Addr, uint64_t TypeSize) const {
  SizeOffsetType SizeOffset = ObjSizeVis.compute(Addr);
  if (!ObjSizeVis.bothKnown(SizeOffset)) return false;
  uint64_t Size = SizeOffset.first.getZExtValue();
  int64_t Offset = SizeOffset.second.getSExtValue();


  return Offset >= 0 && Size >= uint64_t(Offset) &&
         Size - uint64_t(Offset) >= TypeSize / 8;
}
