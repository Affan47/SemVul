SetRepeatedString(
    Message* message, const FieldDescriptor* field,
    int index, const string& value) const {
  USAGE_CHECK_ALL(SetRepeatedString, REPEATED, STRING);
  if (field->is_extension()) {
    MutableExtensionSet(message)->SetRepeatedString(
      field->number(), index, value);
  } else {
    *MutableRepeatedField<string>(message, field, index) = value;
  }
}
