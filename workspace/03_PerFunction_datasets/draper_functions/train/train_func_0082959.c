UnaryType(UnaryOperation* expr) {
  Handle<Object> object = GetInfo(expr->id());
  TypeInfo unknown = TypeInfo::Unknown();
  if (!object->IsCode()) return unknown;
  Handle<Code> code = Handle<Code>::cast(object);
  ASSERT(code->is_unary_op_stub());
  UnaryOpIC::TypeInfo type = static_cast<UnaryOpIC::TypeInfo>(
      code->unary_op_type());
  switch (type) {
    case UnaryOpIC::SMI:
      return TypeInfo::Smi();
    case UnaryOpIC::HEAP_NUMBER:
      return TypeInfo::Double();
    default:
      return unknown;
  }
}
