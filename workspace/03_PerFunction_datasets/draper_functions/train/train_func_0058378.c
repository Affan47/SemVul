PrintFieldValue(
    const Message& message,
    const Reflection* reflection,
    const FieldDescriptor* field,
    int index,
    TextGenerator& generator) {
  GOOGLE_DCHECK(field->is_repeated() || (index == -1))
      << "Index must be -1 for non-repeated fields";

  switch (field->cpp_type()) {
#define OUTPUT_FIELD(CPPTYPE, METHOD, TO_STRING)                             \
      case FieldDescriptor::CPPTYPE_##CPPTYPE:                               \
        generator.Print(TO_STRING(field->is_repeated() ?                     \
          reflection->GetRepeated##METHOD(message, field, index) :           \
          reflection->Get##METHOD(message, field)));                         \
        break;                                                               \

      OUTPUT_FIELD( INT32,  Int32, SimpleItoa);
      OUTPUT_FIELD( INT64,  Int64, SimpleItoa);
      OUTPUT_FIELD(UINT32, UInt32, SimpleItoa);
      OUTPUT_FIELD(UINT64, UInt64, SimpleItoa);
      OUTPUT_FIELD( FLOAT,  Float, SimpleFtoa);
      OUTPUT_FIELD(DOUBLE, Double, SimpleDtoa);
#undef OUTPUT_FIELD

      case FieldDescriptor::CPPTYPE_STRING: {
        string scratch;
        const string& value = field->is_repeated() ?
            reflection->GetRepeatedStringReference(
              message, field, index, &scratch) :
            reflection->GetStringReference(message, field, &scratch);

        generator.Print("\"");
        generator.Print(CEscape(value));
        generator.Print("\"");

        break;
      }

      case FieldDescriptor::CPPTYPE_BOOL:
        if (field->is_repeated()) {
          generator.Print(reflection->GetRepeatedBool(message, field, index)
                          ? "true" : "false");
        } else {
          generator.Print(reflection->GetBool(message, field)
                          ? "true" : "false");
        }
        break;

      case FieldDescriptor::CPPTYPE_ENUM:
        generator.Print(field->is_repeated() ?
          reflection->GetRepeatedEnum(message, field, index)->name() :
          reflection->GetEnum(message, field)->name());
        break;

      case FieldDescriptor::CPPTYPE_MESSAGE:
        Print(field->is_repeated() ?
                reflection->GetRepeatedMessage(message, field, index) :
                reflection->GetMessage(message, field),
              generator);
        break;
  }
}
