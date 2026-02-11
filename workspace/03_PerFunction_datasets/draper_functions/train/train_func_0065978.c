pop(Register dst) {
	EnsureSpace ensure_space(this);
	emit_optional_rex_32(dst);
	emit(0x58 | dst.low_bits());
}
