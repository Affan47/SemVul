ath_rate_attach(struct ath_softc_tgt *sc)
{
	struct atheros_softc *asc;

	asc = adf_os_mem_alloc(sizeof(struct atheros_softc));
	if (asc == NULL)
		return NULL;

	adf_os_mem_set(asc, 0, sizeof(struct atheros_softc));
	asc->arc.arc_space = sizeof(struct atheros_node);

	ar5416AttachRateTables(asc);

	asc->tx_chainmask = 1;

	return &asc->arc;
}
