getEnumName(MVT::SimpleValueType T) {
  switch (T) {
  case MVT::Other:    return "MVT::Other";
  case MVT::i1:       return "MVT::i1";
  case MVT::i8:       return "MVT::i8";
  case MVT::i16:      return "MVT::i16";
  case MVT::i32:      return "MVT::i32";
  case MVT::i64:      return "MVT::i64";
  case MVT::i128:     return "MVT::i128";
  case MVT::iAny:     return "MVT::iAny";
  case MVT::fAny:     return "MVT::fAny";
  case MVT::vAny:     return "MVT::vAny";
  case MVT::f32:      return "MVT::f32";
  case MVT::f64:      return "MVT::f64";
  case MVT::f80:      return "MVT::f80";
  case MVT::f128:     return "MVT::f128";
  case MVT::ppcf128:  return "MVT::ppcf128";
  case MVT::x86mmx:   return "MVT::x86mmx";
  case MVT::Glue:     return "MVT::Glue";
  case MVT::isVoid:   return "MVT::isVoid";
  case MVT::v2i8:     return "MVT::v2i8";
  case MVT::v4i8:     return "MVT::v4i8";
  case MVT::v8i8:     return "MVT::v8i8";
  case MVT::v16i8:    return "MVT::v16i8";
  case MVT::v32i8:    return "MVT::v32i8";
  case MVT::v2i16:    return "MVT::v2i16";
  case MVT::v4i16:    return "MVT::v4i16";
  case MVT::v8i16:    return "MVT::v8i16";
  case MVT::v16i16:   return "MVT::v16i16";
  case MVT::v2i32:    return "MVT::v2i32";
  case MVT::v4i32:    return "MVT::v4i32";
  case MVT::v8i32:    return "MVT::v8i32";
  case MVT::v1i64:    return "MVT::v1i64";
  case MVT::v2i64:    return "MVT::v2i64";
  case MVT::v4i64:    return "MVT::v4i64";
  case MVT::v8i64:    return "MVT::v8i64";
  case MVT::v2f32:    return "MVT::v2f32";
  case MVT::v4f32:    return "MVT::v4f32";
  case MVT::v8f32:    return "MVT::v8f32";
  case MVT::v2f64:    return "MVT::v2f64";
  case MVT::v4f64:    return "MVT::v4f64";
  case MVT::Metadata: return "MVT::Metadata";
  case MVT::iPTR:     return "MVT::iPTR";
  case MVT::iPTRAny:  return "MVT::iPTRAny";
  case MVT::untyped:  return "MVT::untyped";
  default: assert(0 && "ILLEGAL VALUE TYPE!"); return "";
  }
}
