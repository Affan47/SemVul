__emit_pop_reg(struct buffer *buf, enum machine_reg reg)
{
	unsigned char rex_pfx = 0, rm;

	rm = x86_encode_reg(reg);

#ifdef CONFIG_X86_64
	if (reg_high(rm))
		rex_pfx |= REX_B;
#endif
	if (rex_pfx)
		emit(buf, rex_pfx);

	emit(buf, 0x58 + reg_low(rm));
}
