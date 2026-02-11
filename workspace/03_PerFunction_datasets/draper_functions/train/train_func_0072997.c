AddEnum(int number, FieldType type,
                           bool packed, int value,
                           const FieldDescriptor* descriptor) {
  Extension* extension;
  if (MaybeNewExtension(number, descriptor, &extension)) {
    extension->type = type;
    GOOGLE_DCHECK_EQ(cpp_type(extension->type), WireFormatLite::CPPTYPE_ENUM);
    extension->is_repeated = true;
    extension->is_packed = packed;
    extension->repeated_enum_value = new RepeatedField<int>();
  } else {
    GOOGLE_DCHECK_TYPE(*extension, REPEATED, ENUM);
    GOOGLE_DCHECK_EQ(extension->is_packed, packed);
  }
  extension->repeated_enum_value->Add(value);
}
