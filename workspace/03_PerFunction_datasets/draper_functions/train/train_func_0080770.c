SetInt64(int number, int64 value,
    FieldDescriptor::Type type, UnknownFieldSet* unknown_fields) {
  switch (type) {
    case FieldDescriptor::TYPE_INT64:
      unknown_fields->AddVarint(number, static_cast<uint64>(value));
      break;

    case FieldDescriptor::TYPE_SFIXED64:
      unknown_fields->AddFixed64(number, static_cast<uint64>(value));
      break;

    case FieldDescriptor::TYPE_SINT64:
      unknown_fields->AddVarint(number,
          google::protobuf::internal::WireFormatLite::ZigZagEncode64(value));
      break;

    default:
      GOOGLE_LOG(FATAL) << "Invalid wire type for CPPTYPE_INT64: " << type;
      break;
  }
}
