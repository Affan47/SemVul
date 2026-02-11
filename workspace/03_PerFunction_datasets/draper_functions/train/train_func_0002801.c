Clear() {
  _extensions_.Clear();
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (_has_bit(0)) {
      if (java_package_ != &_default_java_package_) {
        java_package_->clear();
      }
    }
    if (_has_bit(1)) {
      if (java_outer_classname_ != &_default_java_outer_classname_) {
        java_outer_classname_->clear();
      }
    }
    java_multiple_files_ = false;
    optimize_for_ = 1;
    cc_generic_services_ = true;
    java_generic_services_ = true;
    py_generic_services_ = true;
  }
  uninterpreted_option_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}
