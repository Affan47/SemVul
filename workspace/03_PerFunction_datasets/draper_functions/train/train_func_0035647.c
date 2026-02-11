smp_loaded_st(const struct smp_sc *sc, const struct smp_seg *sg,
    const struct storage *st)
{
	struct smp_seg *sg2;
	const uint8_t *pst;
	uint64_t o;

	(void)sg;
	pst = (const void *)st;

	if (pst < (sc->base + sc->ident->stuff[SMP_SPC_STUFF]))
		return (0x01);
	if (pst > (sc->base + sc->ident->stuff[SMP_END_STUFF]))
		return (0x02);

	o = pst - sc->base;


	VTAILQ_FOREACH(sg2, &sc->segments, list)
		if (o > sg2->p.offset && (o + sizeof(*st)) < sg2->p.objlist)
			break;
	if (sg2 == NULL)
		return (0x04);
	if (!(sg2->flags & SMP_SEG_LOADED))
		return (0x08);


	if (st->magic != STORAGE_MAGIC)
		return (0x10);

	if (o + st->space >= sg2->p.objlist)
		return (0x20);

	if (st->len > st->space)
		return (0x40);


	return (0);
}
