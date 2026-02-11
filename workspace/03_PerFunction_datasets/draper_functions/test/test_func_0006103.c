bcj_powerpc(
		struct xz_dec_bcj *s, uint8_t *buf, size_t size)
{
	size_t i;
	uint32_t instr;

	for (i = 0; i + 4 <= size; i += 4) {
		instr = get_unaligned_be32(buf + i);
		if ((instr & 0xFC000003) == 0x48000001) {
			instr &= 0x03FFFFFC;
			instr -= s->pos + (uint32_t)i;
			instr &= 0x03FFFFFC;
			instr |= 0x48000001;
			put_unaligned_be32(instr, buf + i);
		}
	}

	return i;
}
