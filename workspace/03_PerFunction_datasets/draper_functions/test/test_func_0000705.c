GetRepeatedStringReference(
    const Message& message, const FieldDescriptor* field,
    int index, string* scratch) const {
  USAGE_CHECK_ALL(GetRepeatedStringReference, REPEATED, STRING);
  if (field->is_extension()) {
    return GetExtensionSet(message).GetRepeatedString(field->number(), index);
  } else {
    return GetRepeatedPtrField<string>(message, field, index);
  }
}
