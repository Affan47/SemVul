ath9k_init_crypto(struct ath_softc *sc)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	unsigned int i = 0;


	common->keymax = AR_KEYTABLE_SIZE;


	for (i = 0; i < common->keymax; i++)
		ath_hw_keyreset(common, (u16) i);


	if (sc->sc_ah->misc_mode & AR_PCU_MIC_NEW_LOC_ENA)
		common->crypt_caps |= ATH_CRYPT_CAP_MIC_COMBINED;
}
