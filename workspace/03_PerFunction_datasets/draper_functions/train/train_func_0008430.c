draw_antic_e_gtia9(int nchars, const UBYTE *antic_memptr, UWORD *ptr, const ULONG *t_pm_scanline_ptr)
{
	ULONG lookup[16];
	if ((unsigned long) ptr & 2) {
		prepare_an_antic_e(nchars, antic_memptr, t_pm_scanline_ptr);
		draw_an_gtia9(t_pm_scanline_ptr);
		return;
	}
	lookup[0] = lookup[1] = lookup[4] = lookup[5] = ANTIC_lookup_gtia9[0];
	lookup[2] = lookup[6] = ANTIC_lookup_gtia9[1];
	lookup[3] = lookup[7] = ANTIC_lookup_gtia9[2];
	lookup[8] = lookup[9] = ANTIC_lookup_gtia9[4];
	lookup[10] = ANTIC_lookup_gtia9[5];
	lookup[11] = ANTIC_lookup_gtia9[6];
	lookup[12] = lookup[13] = ANTIC_lookup_gtia9[8];
	lookup[14] = ANTIC_lookup_gtia9[9];
	lookup[15] = ANTIC_lookup_gtia9[10];
	CHAR_LOOP_BEGIN
		UBYTE screendata = *antic_memptr++;
		WRITE_VIDEO_LONG((ULONG *) ptr, lookup[screendata >> 4]);
		WRITE_VIDEO_LONG((ULONG *) ptr + 1, lookup[screendata & 0xf]);
		if (IS_ZERO_ULONG(t_pm_scanline_ptr))
			ptr += 4;
		else {
			const UBYTE *c_pm_scanline_ptr = (const UBYTE *) t_pm_scanline_ptr;
			int k = 4;
			UBYTE pm_reg;
			do {
				pm_reg = pm_lookup_ptr[*c_pm_scanline_ptr++];
				if (pm_reg) {
					if (pm_reg == L_PF3) {
						UBYTE tmp = k > 2 ? screendata >> 4 : screendata & 0xf;
#ifdef USE_COLOUR_TRANSLATION_TABLE
						WRITE_VIDEO(ptr, colour_translation_table[tmp | GTIA_COLPF3]);
#else
						WRITE_VIDEO(ptr, tmp | ((UWORD)tmp << 8) | ANTIC_cl[C_PF3]);
#endif
					}
					else
					{
						WRITE_VIDEO(ptr, COLOUR(pm_reg));
					}
				}
				ptr++;
			} while (--k);
		}
		t_pm_scanline_ptr++;
	CHAR_LOOP_END
	do_border();
}
