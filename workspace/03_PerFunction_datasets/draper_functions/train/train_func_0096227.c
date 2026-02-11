snd_emu10k1_audigy_write_op(struct snd_emu10k1_fx8010_code *icode,
					unsigned int *ptr,
					u32 op, u32 r, u32 a, u32 x, u32 y)
{
	u_int32_t *code;
	if (snd_BUG_ON(*ptr >= 1024))
		return;
	code = (u_int32_t __force *)icode->code + (*ptr) * 2;
	set_bit(*ptr, icode->code_valid);
	code[0] = ((x & 0x7ff) << 12) | (y & 0x7ff);
	code[1] = ((op & 0x0f) << 24) | ((r & 0x7ff) << 12) | (a & 0x7ff);
	(*ptr)++;
}
