page_cur_lcg_prng(void)

{
#define LCG_a	1103515245
#define LCG_c	12345
	static ib_uint64_t	lcg_current = 0;
	static ibool		initialized = FALSE;

	if (!initialized) {
		lcg_current = (ib_uint64_t) ut_time_us(NULL);
		initialized = TRUE;
	}


	lcg_current = LCG_a * lcg_current + LCG_c;

	return(lcg_current);
}
