GetRepeatedEnum(
    const Message& message, const FieldDescriptor* field, int index) const {
  USAGE_CHECK_ALL(GetRepeatedEnum, REPEATED, ENUM);

  int value;
  if (field->is_extension()) {
    value = GetExtensionSet(message).GetRepeatedEnum(field->number(), index);
  } else {
    value = GetRepeatedField<int>(message, field, index);
  }
  const EnumValueDescriptor* result =
    field->enum_type()->FindValueByNumber(value);
  GOOGLE_CHECK(result != NULL);
  return result;
}
