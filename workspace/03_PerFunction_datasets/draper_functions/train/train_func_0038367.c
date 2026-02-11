SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  ::google::protobuf::uint8* raw_buffer = output->GetDirectBufferForNBytesAndAdvance(_cached_size_);
  if (raw_buffer != NULL) {
    FileOptions::SerializeWithCachedSizesToArray(raw_buffer);
    return;
  }


  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->java_package().data(), this->java_package().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->java_package(), output);
  }


  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->java_outer_classname().data(), this->java_outer_classname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      8, this->java_outer_classname(), output);
  }


  if (_has_bit(3)) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      9, this->optimize_for(), output);
  }


  if (_has_bit(2)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(10, this->java_multiple_files(), output);
  }


  for (int i = 0; i < this->uninterpreted_option_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageNoVirtual(
      999, this->uninterpreted_option(i), output);
  }


  _extensions_.SerializeWithCachedSizes(
      1000, 536870912, output);

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}
