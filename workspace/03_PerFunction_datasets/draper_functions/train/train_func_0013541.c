SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {

  for (int i = 0; i < this->name_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->name(i), output);
  }


  if (has_identifier_value()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->identifier_value().data(), this->identifier_value().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      3, this->identifier_value(), output);
  }


  if (has_positive_int_value()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(4, this->positive_int_value(), output);
  }


  if (has_negative_int_value()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(5, this->negative_int_value(), output);
  }


  if (has_double_value()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(6, this->double_value(), output);
  }


  if (has_string_value()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      7, this->string_value(), output);
  }


  if (has_aggregate_value()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->aggregate_value().data(), this->aggregate_value().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      8, this->aggregate_value(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}
