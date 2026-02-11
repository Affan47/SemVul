RemoveLast(
    Message* message,
    const FieldDescriptor* field) const {
  USAGE_CHECK_MESSAGE_TYPE(RemoveLast);
  USAGE_CHECK_REPEATED(RemoveLast);

  if (field->is_extension()) {
    MutableExtensionSet(message)->RemoveLast(field->number());
  } else {
    switch (field->cpp_type()) {
#define HANDLE_TYPE(UPPERCASE, LOWERCASE)                                     \
      case FieldDescriptor::CPPTYPE_##UPPERCASE :                             \
        MutableRaw<RepeatedField<LOWERCASE> >(message, field)->RemoveLast();  \
        break

      HANDLE_TYPE( INT32,  int32);
      HANDLE_TYPE( INT64,  int64);
      HANDLE_TYPE(UINT32, uint32);
      HANDLE_TYPE(UINT64, uint64);
      HANDLE_TYPE(DOUBLE, double);
      HANDLE_TYPE( FLOAT,  float);
      HANDLE_TYPE(  BOOL,   bool);
      HANDLE_TYPE(  ENUM,    int);
#undef HANDLE_TYPE

      case FieldDescriptor::CPPTYPE_STRING:
        switch (field->options().ctype()) {
          default:
          case FieldOptions::STRING:
            MutableRaw<RepeatedPtrField<string> >(message, field)->RemoveLast();
            break;
        }
        break;

      case FieldDescriptor::CPPTYPE_MESSAGE:
        MutableRaw<RepeatedPtrFieldBase>(message, field)
            ->RemoveLast<GenericTypeHandler<Message> >();
        break;
    }
  }
}
