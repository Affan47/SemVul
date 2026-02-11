jisident(c)
char	c;
{
#ifdef USE_CTYPE
	return (IdChartable[ZXC(c)] & (1 << curbuf->b_major)) != 0 || jisword(c);
#else
	return (IdChartable[ZXC(c)] & (1 << curbuf->b_major)) != 0;
#endif
}
