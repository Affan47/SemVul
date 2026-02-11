get_num(bio_file_t *h, int base, int figures)
{
	int value = 0;
	while(figures--)
	{
		int n = get_figure(h, base);
		if(n < 0)
			return n;
		value *= base;
		value += n;
	}
	return value;
}
