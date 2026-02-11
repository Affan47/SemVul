op_calc1(UINT32 phase, unsigned int env, signed int pm, unsigned int wave_tab)
{
	UINT32 p;

	p = (env<<4) + sin_tab[wave_tab + ((((signed int)((phase & ~FREQ_MASK) + pm))>>FREQ_SH) & SIN_MASK)];

	if (p >= TL_TAB_LEN)
		return 0;
	return tl_tab[p];
}
