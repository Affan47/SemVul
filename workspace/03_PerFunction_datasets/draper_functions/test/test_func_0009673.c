GetName() {
  switch (op_) {
    case Token::SUB:
      if (negative_zero_ == kStrictNegativeZero) {
        return overwrite_ == UNARY_OVERWRITE
            ? "GenericUnaryOpStub_SUB_Overwrite_Strict0"
            : "GenericUnaryOpStub_SUB_Alloc_Strict0";
      } else {
        return overwrite_ == UNARY_OVERWRITE
            ? "GenericUnaryOpStub_SUB_Overwrite_Ignore0"
            : "GenericUnaryOpStub_SUB_Alloc_Ignore0";
      }
    case Token::BIT_NOT:
      return overwrite_ == UNARY_OVERWRITE
          ? "GenericUnaryOpStub_BIT_NOT_Overwrite"
          : "GenericUnaryOpStub_BIT_NOT_Alloc";
    default:
      UNREACHABLE();
      return "<unknown>";
  }
}
