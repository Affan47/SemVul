copy_transparent8
	(
	unsigned char *src_pixels,
	int srcw, int srch,
	int destx, int desty
	)
	{
	int srcx = 0, srcy = 0;
	int src_width = srcw;

	if (!clip(srcx, srcy, srcw, srch, destx, desty))
		return;
	unsigned short *to = get_pixels() + desty*line_width + destx;
	unsigned char *from = src_pixels + srcy*src_width + srcx;
	int to_next = line_width - srcw;
	int from_next = src_width - srcw;
	while (srch--)
		{
		for (int cnt = srcw; cnt; cnt--, to++)
			{
			register int chr = *from++;
			if (chr)
				*to = palette[chr];
			}
		to += to_next;
		from += from_next;
		}
	}
