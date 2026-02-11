smp_close(const struct stevedore *st)
{
	struct smp_sc	*sc;

	ASSERT_CLI();

	CAST_OBJ_NOTNULL(sc, st->priv, SMP_SC_MAGIC);
	Lck_Lock(&sc->mtx);
	smp_close_seg(sc, sc->cur_seg);
	Lck_Unlock(&sc->mtx);


}
