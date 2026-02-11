hw_cursor_setData2(struct lynx_cursor *cursor,
			u16 rop, const u8 *pcol, const u8 *pmsk)
{
	int i, j, count, pitch, offset;
	u8 color, mask;
	u16 data;
	void __iomem *pbuffer, *pstart;


	pitch = cursor->w >> 3;


	count = pitch * cursor->h;


	offset = cursor->maxW * 2 / 8;

	data = 0;
	pstart = cursor->vstart;
	pbuffer = pstart;

	for (i = 0; i < count; i++) {
		color = *pcol++;
		mask = *pmsk++;
		data = 0;

		for (j = 0; j < 8; j++) {
			if (mask & (1<<j))
				data |= ((color & (1<<j))?1:2)<<(j*2);
		}
		iowrite16(data, pbuffer);


		if (!(i&(pitch-1))) {

			pstart += offset;
			pbuffer = pstart;
		} else {
			pbuffer += sizeof(u16);
		}

	}
}
