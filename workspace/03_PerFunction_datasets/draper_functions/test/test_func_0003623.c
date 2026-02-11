draw_circle_line(struct mame_bitmap *bitmap, int x, int y, int l)
{
	if (y >= 0 && y <= bitmap->height - 1)
	{
		const UINT16* p = LSFR + (UINT16) (512 * y);

		UINT16* pLine = bitmap->line[y];

		int h1 = x - 2 * l;
		int h2 = x + 2 * l;

		if (h1 < 0)
			h1 = 0;
		if (h2 > bitmap->width - 1)
			h2 = bitmap->width - 1;

		for (x = h1; x <= h2; x++)
		{
			if (starshp1_circle_mod)
			{
				if (p[x] & 1)
				{
					pLine[x] = 5;
				}
			}
			else
			{
				pLine[x] = 7;
			}
		}
	}
}
