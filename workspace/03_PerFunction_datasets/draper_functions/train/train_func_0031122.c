gdsc_force_mem_on(struct gdsc *sc)
{
	int i;
	u32 mask = RETAIN_MEM | RETAIN_PERIPH;

	for (i = 0; i < sc->cxc_count; i++)
		regmap_update_bits(sc->regmap, sc->cxcs[i], mask, mask);
}
