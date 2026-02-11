Swap(DescriptorProto* other) {
  if (other != this) {
    std::swap(name_, other->name_);
    field_.Swap(&other->field_);
    extension_.Swap(&other->extension_);
    nested_type_.Swap(&other->nested_type_);
    enum_type_.Swap(&other->enum_type_);
    extension_range_.Swap(&other->extension_range_);
    std::swap(options_, other->options_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}
