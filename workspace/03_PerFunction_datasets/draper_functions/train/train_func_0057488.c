setcc(Condition cc, Register reg) {
  if (cc > last_condition) {
    movb(reg, Immediate(cc == always ? 1 : 0));
    return;
  }
  EnsureSpace ensure_space(this);
  ASSERT(is_uint4(cc));
  if (reg.code() > 3) {
    emit_rex_32(reg);
  }
  emit(0x0F);
  emit(0x90 | cc);
  emit_modrm(0x0, reg);
}
