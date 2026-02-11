testq(Register dst, Immediate mask) {
  EnsureSpace ensure_space(this);
  if (dst.is(rax)) {
    emit_rex_64();
    emit(0xA9);
    emit(mask);
  } else {
    emit_rex_64(dst);
    emit(0xF7);
    emit_modrm(0, dst);
    emit(mask);
  }
}
