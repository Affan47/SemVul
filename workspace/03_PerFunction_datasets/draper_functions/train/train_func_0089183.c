__emit_test_imm_memdisp(struct buffer *buf,
				    int rex_w,
				    long imm,
				    long disp)
{


	if (rex_w)
		emit(buf, REX_W);

	if (is_imm_8(imm))
		emit(buf, 0xf6);
	else
		emit(buf, 0xf7);

	emit(buf, 0x04);
	emit(buf, 0x25);
	emit_imm32(buf, disp);
	emit_imm(buf, imm);
}
