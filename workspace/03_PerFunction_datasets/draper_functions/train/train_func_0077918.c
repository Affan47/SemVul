groestl_big_init(sph_groestl_big_context *sc, unsigned out_size)
{
	size_t u;

	sc->ptr = 0;
#if SPH_GROESTL_64
	for (u = 0; u < 15; u ++)
		sc->state.wide[u] = 0;
#if USE_LE
	sc->state.wide[15] = ((sph_u64)(out_size & 0xFF) << 56)
		| ((sph_u64)(out_size & 0xFF00) << 40);
#else
	sc->state.wide[15] = (sph_u64)out_size;
#endif
#else
	for (u = 0; u < 31; u ++)
		sc->state.narrow[u] = 0;
#if USE_LE
	sc->state.narrow[31] = ((sph_u32)(out_size & 0xFF) << 24)
		| ((sph_u32)(out_size & 0xFF00) << 8);
#else
	sc->state.narrow[31] = (sph_u32)out_size;
#endif
#endif
#if SPH_64
	sc->count = 0;
#else
	sc->count_high = 0;
	sc->count_low = 0;
#endif
}
