ByteSize() const {
  int total_size = 0;

  if (_has_bits_[1 / 32] & (0xffu << (1 % 32))) {

    if (has_identifier_value()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->identifier_value());
    }


    if (has_positive_int_value()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->positive_int_value());
    }


    if (has_negative_int_value()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int64Size(
          this->negative_int_value());
    }


    if (has_double_value()) {
      total_size += 1 + 8;
    }


    if (has_string_value()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->string_value());
    }


    if (has_aggregate_value()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->aggregate_value());
    }

  }

  total_size += 1 * this->name_size();
  for (int i = 0; i < this->name_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->name(i));
  }

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
