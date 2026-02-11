ath_init_tgt(void *Context, A_UINT16 Command,
			 A_UINT16 SeqNo, A_UINT8 *data, a_int32_t datalen)
{
	struct ath_softc_tgt *sc = (struct ath_softc_tgt *)Context;
	struct ath_hal *ah = sc->sc_ah;

	sc->sc_imask = HAL_INT_RX | HAL_INT_TX
		| HAL_INT_RXEOL | HAL_INT_RXORN
		| HAL_INT_FATAL | HAL_INT_GLOBAL;

	sc->sc_imask |= HAL_INT_GTT;

	if (ath_hal_getcapability(ah, HAL_CAP_HT))
		sc->sc_imask |= HAL_INT_CST;

	adf_os_setup_intr(sc->sc_dev, ath_intr);
	ah->ah_setInterrupts(ah, sc->sc_imask);

	wmi_cmd_rsp(sc->tgt_wmi_handle, Command, SeqNo, NULL, 0);
}
