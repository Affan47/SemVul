copy
	(
	int srcx, int srcy,
	int srcw, int srch,
	int destx, int desty
	)
	{
	int ynext, yfrom, yto;
	if (srcy >= desty)
		{
		ynext = line_width;
		yfrom = srcy;
		yto = desty;
		}
	else
		{
		ynext = -line_width;
		yfrom = srcy + srch - 1;
		yto = desty + srch - 1;
		}
	unsigned char *to = bits + yto*line_width + destx;
	unsigned char *from = bits + yfrom*line_width + srcx;

	while (srch--)
		{
		std::memmove((char *) to, (char *) from, srcw);
		to += ynext;
		from += ynext;
		}
	}
