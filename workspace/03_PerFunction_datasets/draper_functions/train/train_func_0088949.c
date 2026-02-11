sma_free_space(const struct stevedore *st)
{
	struct sma_sc *sma_sc;

	CAST_OBJ_NOTNULL(sma_sc, st->priv, SMA_SC_MAGIC);
	return (sma_sc->sma_max - sma_sc->sma_alloc);
}
