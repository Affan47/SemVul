MutableString(int number, FieldType type,
                                    const FieldDescriptor* descriptor) {
  Extension* extension;
  if (MaybeNewExtension(number, descriptor, &extension)) {
    extension->type = type;
    GOOGLE_DCHECK_EQ(cpp_type(extension->type), WireFormatLite::CPPTYPE_STRING);
    extension->is_repeated = false;
    extension->string_value = new string;
  } else {
    GOOGLE_DCHECK_TYPE(*extension, OPTIONAL, STRING);
  }
  extension->is_cleared = false;
  return extension->string_value;
}
