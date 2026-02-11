find_first_not_of(char c, size_type pos) const {
  if (length_ == 0)
    return npos;

  for (; pos < length_; ++pos) {
    if (ptr_[pos] != c) {
      return pos;
    }
  }
  return npos;
}
