GetTypeInfo(Handle<Object> operand) {
  ::v8::internal::TypeInfo operand_type =
      ::v8::internal::TypeInfo::TypeFromValue(operand);
  if (operand_type.IsSmi()) {
    return SMI;
  } else if (operand_type.IsNumber()) {
    return HEAP_NUMBER;
  } else {
    return GENERIC;
  }
}
