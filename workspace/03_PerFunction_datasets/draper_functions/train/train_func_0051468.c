ByteSize() const {
  int total_size = 0;


  {
    int data_size = 0;
    for (int i = 0; i < this->path_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        Int32Size(this->path(i));
    }
    if (data_size > 0) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(data_size);
    }
    _path_cached_byte_size_ = data_size;
    total_size += data_size;
  }


  {
    int data_size = 0;
    for (int i = 0; i < this->span_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        Int32Size(this->span(i));
    }
    if (data_size > 0) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(data_size);
    }
    _span_cached_byte_size_ = data_size;
    total_size += data_size;
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
