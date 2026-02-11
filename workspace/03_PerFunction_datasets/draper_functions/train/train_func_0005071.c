gf_bs_read_long_int(GF_BitStream *bs, u32 nBits)
{
	u64 ret = 0;
	if (nBits>64) {
		gf_bs_read_long_int(bs, nBits-64);
		ret = gf_bs_read_long_int(bs, 64);
	} else {
		while (nBits-- > 0) {
			ret <<= 1;
			ret |= gf_bs_read_bit(bs);
		}
	}
	return ret;
}
