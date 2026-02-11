Swap(FileDescriptorProto* other) {
  if (other != this) {
    std::swap(name_, other->name_);
    std::swap(package_, other->package_);
    dependency_.Swap(&other->dependency_);
    message_type_.Swap(&other->message_type_);
    enum_type_.Swap(&other->enum_type_);
    service_.Swap(&other->service_);
    extension_.Swap(&other->extension_);
    std::swap(options_, other->options_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}
