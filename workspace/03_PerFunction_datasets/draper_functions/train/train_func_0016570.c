SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {

  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->name().data(), this->name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->name(), output);
  }


  for (int i = 0; i < this->field_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->field(i), output);
  }


  for (int i = 0; i < this->nested_type_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, this->nested_type(i), output);
  }


  for (int i = 0; i < this->enum_type_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, this->enum_type(i), output);
  }


  for (int i = 0; i < this->extension_range_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      5, this->extension_range(i), output);
  }


  for (int i = 0; i < this->extension_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      6, this->extension(i), output);
  }


  if (_has_bit(6)) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      7, this->options(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}
