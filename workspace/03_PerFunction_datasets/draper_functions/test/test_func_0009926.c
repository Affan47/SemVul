Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    start_ = 0;
    end_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}
