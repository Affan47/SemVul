Clear() {
  _extensions_.Clear();
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    message_set_wire_format_ = false;
    no_standard_descriptor_accessor_ = false;
  }
  uninterpreted_option_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}
