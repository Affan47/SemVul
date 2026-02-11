evalAsLongV() {
  IdlLongVal e = e_->evalAsLongV();

  if (e.negative)
    return IdlLongVal(IDL_ULong(-e.s));
  else {
    if (e.u > 0x80000000)
      IdlError(file(), line(), "Result of unary minus overflows");
    return IdlLongVal(IDL_Long(-e.u));
  }
}
