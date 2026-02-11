movl(Register dst, Register src) {
  EnsureSpace ensure_space(this);
  if (src.low_bits() == 4) {
    emit_optional_rex_32(src, dst);
    emit(0x89);
    emit_modrm(src, dst);
  } else {
    emit_optional_rex_32(dst, src);
    emit(0x8B);
    emit_modrm(dst, src);
  }
}
