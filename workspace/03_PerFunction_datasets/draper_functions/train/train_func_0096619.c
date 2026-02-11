fz_paint_span_N(byte * restrict dp, byte * restrict sp, int n, int w)
{
	while (w--)
	{
		int k = n;
		int t = FZ_EXPAND(255 - sp[n-1]);
		while (k--)
		{
			*dp = *sp++ + FZ_COMBINE(*dp, t);
			dp++;
		}
	}
}
