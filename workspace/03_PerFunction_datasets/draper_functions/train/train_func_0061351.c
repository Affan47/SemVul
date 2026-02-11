pfield_doline (int lineno)
{
	int wordcount = dp_for_drawing->plflinelen;
	uae_u32 *data = pixdata.apixels_l + MAX_PIXELS_PER_LINE / 4;

#ifdef SMART_UPDATE
#define DATA_POINTER(n) ((debug_bpl_mask & (1 << n)) ? (line_data[lineno] + (n) * MAX_WORDS_PER_LINE * 2) : (debug_bpl_mask_one ? all_ones : all_zeros))
	real_bplpt[0] = DATA_POINTER (0);
	real_bplpt[1] = DATA_POINTER (1);
	real_bplpt[2] = DATA_POINTER (2);
	real_bplpt[3] = DATA_POINTER (3);
	real_bplpt[4] = DATA_POINTER (4);
	real_bplpt[5] = DATA_POINTER (5);
#ifdef AGA
	real_bplpt[6] = DATA_POINTER (6);
	real_bplpt[7] = DATA_POINTER (7);
#endif
#endif

	switch (bplplanecnt) {
	default: break;
	case 0: memset (data, 0, wordcount * 32); break;
	case 1: pfield_doline_n1 (data, wordcount); break;
	case 2: pfield_doline_n2 (data, wordcount); break;
	case 3: pfield_doline_n3 (data, wordcount); break;
	case 4: pfield_doline_n4 (data, wordcount); break;
	case 5: pfield_doline_n5 (data, wordcount); break;
	case 6: pfield_doline_n6 (data, wordcount); break;
#ifdef AGA
	case 7: pfield_doline_n7 (data, wordcount); break;
	case 8: pfield_doline_n8 (data, wordcount); break;
#endif
	}
}
