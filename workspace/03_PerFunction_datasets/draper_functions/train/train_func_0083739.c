partprod(u32 xres)
{
	int i;

	for (i = 0; pp_table[i].width && pp_table[i].width != xres; i++)
		;
	if (pp_table[i].width == 0)
		DPRINTK("invalid width %u\n", xres);
	return pp_table[i].pp;
}
