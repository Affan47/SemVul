cvttss2si(Register dst, XMMRegister src) {
	EnsureSpace ensure_space(this);
	emit(0xF3);
	emit_optional_rex_32(dst, src);
	emit(0x0F);
	emit(0x2C);
	emit_sse_operand(dst, src);
}
