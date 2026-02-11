SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {

  if (_has_bit(0)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(1, this->message_set_wire_format(), output);
  }


  if (_has_bit(1)) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->no_standard_descriptor_accessor(), output);
  }


  for (int i = 0; i < this->uninterpreted_option_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      999, this->uninterpreted_option(i), output);
  }


  _extensions_.SerializeWithCachedSizes(
      1000, 536870912, output);

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}
