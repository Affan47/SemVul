ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {

    if (has_java_package()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->java_package());
    }


    if (has_java_outer_classname()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->java_outer_classname());
    }


    if (has_java_multiple_files()) {
      total_size += 1 + 1;
    }


    if (has_java_generate_equals_and_hash()) {
      total_size += 2 + 1;
    }


    if (has_optimize_for()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->optimize_for());
    }


    if (has_cc_generic_services()) {
      total_size += 2 + 1;
    }


    if (has_java_generic_services()) {
      total_size += 2 + 1;
    }


    if (has_py_generic_services()) {
      total_size += 2 + 1;
    }

  }

  total_size += 2 * this->uninterpreted_option_size();
  for (int i = 0; i < this->uninterpreted_option_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->uninterpreted_option(i));
  }

  total_size += _extensions_.ByteSize();

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}
