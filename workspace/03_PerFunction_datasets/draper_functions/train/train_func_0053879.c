init(LiveIntervalUnion::Allocator &Alloc,
                                    unsigned NSize) {

  if (NSize == Size)
    return;
  clear();
  Size = NSize;
  LIUs = static_cast<LiveIntervalUnion*>(
    malloc(sizeof(LiveIntervalUnion)*NSize));
  for (unsigned i = 0; i != Size; ++i)
    new(LIUs + i) LiveIntervalUnion(Alloc);
}
