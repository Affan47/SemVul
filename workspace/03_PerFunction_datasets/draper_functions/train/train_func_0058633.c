LiveRangeFor(int index) {
  if (index >= live_ranges_.length()) {
    live_ranges_.AddBlock(NULL, index - live_ranges_.length() + 1);
  }
  LiveRange* result = live_ranges_[index];
  if (result == NULL) {
    result = new LiveRange(index);
    live_ranges_[index] = result;
  }
  return result;
}
