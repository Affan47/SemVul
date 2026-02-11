AddEnum(
    Message* message, const FieldDescriptor* field,
    const EnumValueDescriptor* value) const {
  USAGE_CHECK_ALL(AddEnum, REPEATED, ENUM);
  USAGE_CHECK_ENUM_VALUE(AddEnum);

  if (field->is_extension()) {
    MutableExtensionSet(message)->AddEnum(field->number(), field->type(),
                                          field->options().packed(),
                                          value->number());
  } else {
    AddField<int>(message, field, value->number());
  }
}
