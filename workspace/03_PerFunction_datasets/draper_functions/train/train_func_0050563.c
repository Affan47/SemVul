testl(Register dst, Register src) {
  EnsureSpace ensure_space(this);
  last_pc_ = pc_;
  if (src.low_bits() == 4) {
    emit_optional_rex_32(src, dst);
    emit(0x85);
    emit_modrm(src, dst);
  } else {
    emit_optional_rex_32(dst, src);
    emit(0x85);
    emit_modrm(dst, src);
  }
}
