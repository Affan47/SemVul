attachRangesOrLowHighPC(
    DIE &Die, const SmallVectorImpl<InsnRange> &Ranges) {
  SmallVector<RangeSpan, 2> List;
  List.reserve(Ranges.size());
  for (const InsnRange &R : Ranges)
    List.push_back(RangeSpan(DD->getLabelBeforeInsn(R.first),
                             DD->getLabelAfterInsn(R.second)));
  attachRangesOrLowHighPC(Die, std::move(List));
}
