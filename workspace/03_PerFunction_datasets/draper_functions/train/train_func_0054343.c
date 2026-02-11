SelectInt64Count(int64_t Imm) {
  unsigned Count = SelectInt64CountDirect(Imm);
  if (Count == 1)
    return Count;

  for (unsigned r = 1; r < 63; ++r) {
    uint64_t RImm = Rot64(Imm, r);
    unsigned RCount = SelectInt64CountDirect(RImm) + 1;
    Count = std::min(Count, RCount);


    unsigned LS = findLastSet(RImm);
    if (LS != r-1)
      continue;

    uint64_t OnesMask = -(int64_t) (UINT64_C(1) << (LS+1));
    uint64_t RImmWithOnes = RImm | OnesMask;

    RCount = SelectInt64CountDirect(RImmWithOnes) + 1;
    Count = std::min(Count, RCount);
  }

  return Count;
}
