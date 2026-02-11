AddSuffix(int id) {
  if (rune_range_.begin == 0) {
    rune_range_.begin = id;
    return;
  }

  int alt = AllocInst(1);
  if (alt < 0) {
    rune_range_.begin = 0;
    return;
  }
  inst_[alt].InitAlt(rune_range_.begin, id);
  rune_range_.begin = alt;
}
