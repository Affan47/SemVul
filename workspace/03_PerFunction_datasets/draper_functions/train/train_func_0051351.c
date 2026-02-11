immediate_arithmetic_op_16(byte subcode,
                                           const Operand& dst,
                                           Immediate src) {
  EnsureSpace ensure_space(this);
  emit(0x66);
  emit_optional_rex_32(dst);
  if (is_int8(src.value_)) {
    emit(0x83);
    emit_operand(subcode, dst);
    emit(src.value_);
  } else {
    emit(0x81);
    emit_operand(subcode, dst);
    emitw(src.value_);
  }
}
