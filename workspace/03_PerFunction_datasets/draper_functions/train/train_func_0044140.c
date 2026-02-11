real_type(FieldType type) {
  GOOGLE_DCHECK(type > 0 && type <= FieldDescriptor::MAX_TYPE);
  return static_cast<FieldDescriptor::Type>(type);
}
