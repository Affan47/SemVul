gf_bs_write_int(GF_BitStream *bs, s32 value, s32 nBits)
{
	value <<= sizeof (s32) * 8 - nBits;
	while (--nBits >= 0) {
		BS_WriteBit (bs, value < 0);
		value <<= 1;
	}
}
