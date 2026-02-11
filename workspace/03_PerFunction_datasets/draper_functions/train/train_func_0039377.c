NumberOfCapturingGroups() const {
  if (suffix_regexp_ == NULL)
    return -1;
  int n;
  ATOMIC_LOAD_RELAXED(n, &num_captures_);
  if (n == -1) {
    n = suffix_regexp_->NumCaptures();
    ATOMIC_STORE_RELAXED(&num_captures_, n);
  }
  return n;
}
