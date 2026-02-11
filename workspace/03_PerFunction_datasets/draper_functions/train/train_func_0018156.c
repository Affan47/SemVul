SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  ::google::protobuf::uint8* raw_buffer = output->GetDirectBufferForNBytesAndAdvance(_cached_size_);
  if (raw_buffer != NULL) {
    ServiceDescriptorProto::SerializeWithCachedSizesToArray(raw_buffer);
    return;
  }


  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->name(), output);
  }


  for (int i = 0; i < this->method_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageNoVirtual(
      2, this->method(i), output);
  }


  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageNoVirtual(
      3, this->options(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}
