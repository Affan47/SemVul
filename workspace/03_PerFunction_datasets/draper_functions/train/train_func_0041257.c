SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  ::google::protobuf::uint8* raw_buffer = output->GetDirectBufferForNBytesAndAdvance(_cached_size_);
  if (raw_buffer != NULL) {
    MethodDescriptorProto::SerializeWithCachedSizesToArray(raw_buffer);
    return;
  }


  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->name(), output);
  }


  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->input_type().data(), this->input_type().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->input_type(), output);
  }


  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->output_type().data(), this->output_type().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->output_type(), output);
  }


  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageNoVirtual(
      4, this->options(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}
