AddString(int number, FieldType type,
                                const FieldDescriptor* descriptor) {
  Extension* extension;
  if (MaybeNewExtension(number, descriptor, &extension)) {
    extension->type = type;
    GOOGLE_DCHECK_EQ(cpp_type(extension->type), WireFormatLite::CPPTYPE_STRING);
    extension->is_repeated = true;
    extension->is_packed = false;
    extension->repeated_string_value = new RepeatedPtrField<string>();
  } else {
    GOOGLE_DCHECK_TYPE(*extension, REPEATED, STRING);
  }
  return extension->repeated_string_value->Add();
}
