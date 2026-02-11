AddRangeToSet(ZoneList<CharacterRange>* set, CharacterRange range) {
  if (set == NULL) return;
  ASSERT(set->length() == 0 || set->at(set->length() - 1).to() < range.from());
  int n = set->length();
  if (n > 0) {
    CharacterRange lastRange = set->at(n - 1);
    if (lastRange.to() == range.from() - 1) {
      set->at(n - 1) = CharacterRange(lastRange.from(), range.to());
      return;
    }
  }
  set->Add(range);
}
