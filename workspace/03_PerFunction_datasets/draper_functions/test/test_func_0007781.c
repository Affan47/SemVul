SetString(
    Message* message, const FieldDescriptor* field,
    const string& value) const {
  USAGE_CHECK_ALL(SetString, SINGULAR, STRING);
  if (field->is_extension()) {
    return MutableExtensionSet(message)->SetString(field->number(),
                                                   field->type(), value);
  } else {
    string** ptr = MutableField<string*>(message, field);
    if (*ptr == DefaultRaw<const string*>(field)) {
      *ptr = new string(value);
    } else {
      (*ptr)->assign(value);
    }
  }
}
