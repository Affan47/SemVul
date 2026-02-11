BinaryType(BinaryOperation* expr) {
  Handle<Object> object = GetInfo(expr->id());
  TypeInfo unknown = TypeInfo::Unknown();
  if (!object->IsCode()) return unknown;
  Handle<Code> code = Handle<Code>::cast(object);
  if (code->is_binary_op_stub()) {
    BinaryOpIC::TypeInfo type = static_cast<BinaryOpIC::TypeInfo>(
        code->binary_op_type());
    BinaryOpIC::TypeInfo result_type = static_cast<BinaryOpIC::TypeInfo>(
        code->binary_op_result_type());

    switch (type) {
      case BinaryOpIC::UNINITIALIZED:

        return TypeInfo::Uninitialized();
      case BinaryOpIC::SMI:
        switch (result_type) {
          case BinaryOpIC::UNINITIALIZED:
          case BinaryOpIC::SMI:
            return TypeInfo::Smi();
          case BinaryOpIC::INT32:
            return TypeInfo::Integer32();
          case BinaryOpIC::HEAP_NUMBER:
            return TypeInfo::Double();
          default:
            return unknown;
        }
      case BinaryOpIC::INT32:
        if (expr->op() == Token::DIV ||
            result_type == BinaryOpIC::HEAP_NUMBER) {
          return TypeInfo::Double();
        }
        return TypeInfo::Integer32();
      case BinaryOpIC::HEAP_NUMBER:
        return TypeInfo::Double();
      case BinaryOpIC::BOTH_STRING:
        return TypeInfo::String();
      case BinaryOpIC::STRING:
      case BinaryOpIC::GENERIC:
        return unknown;
     default:
        return unknown;
    }
  }
  return unknown;
}
