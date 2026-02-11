check_dsp_e1(const u8 *dsp, unsigned int len)
{
	u8 pagecount, blockcount;
	u16 blocksize;
	u32 pageoffset;
	unsigned int i, j, p, pp;

	pagecount = FW_GET_BYTE(dsp);
	p = 1;


	if (p + 4 * pagecount > len)
		return 1;

	for (i = 0; i < pagecount; i++) {

		pageoffset = get_unaligned_le32(dsp + p);
		p += 4;

		if (pageoffset == 0)
			continue;


		if (pageoffset >= len)
			return 1;

		pp = pageoffset;
		blockcount = FW_GET_BYTE(dsp + pp);
		pp += 1;

		for (j = 0; j < blockcount; j++) {


			if (pp + 4 > len)
				return 1;

			pp += 2;
			blocksize = get_unaligned_le16(dsp + pp);
			pp += 2;


			if (pp + blocksize > len)
				return 1;

			pp += blocksize;
		}
	}

	return 0;
}
