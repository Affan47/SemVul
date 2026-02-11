IsClamped() const {
  return used_digits_ == 0 || bigits_[used_digits_ - 1] != 0;
}
