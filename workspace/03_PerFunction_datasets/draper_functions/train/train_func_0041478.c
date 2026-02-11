AddInverse(ZoneList<CharacterRange>* ranges) {
  ranges->Sort(CompareRangeByFrom);
  uc16 last = 0;
  for (int i = 0; i < ranges->length(); i++) {
    CharacterRange range = ranges->at(i);
    if (last < range.from())
      AddRange(CharacterRange(last, range.from() - 1));
    if (range.to() >= last) {
      if (range.to() == String::kMaxUC16CharCode) {
        return;
      } else {
        last = range.to() + 1;
      }
    }
  }
  AddRange(CharacterRange(last, String::kMaxUC16CharCode));
}
