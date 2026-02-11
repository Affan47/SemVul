tgt_HTCRecv_cabhandler(HTC_ENDPOINT_ID EndPt, adf_nbuf_t hdr_buf,
				   adf_nbuf_t buf, void *ServiceCtx)
{
	struct ath_softc_tgt *sc = (struct ath_softc_tgt *)ServiceCtx;
	struct ath_hal *ah = sc->sc_ah;
	a_uint64_t tsf;
	a_uint32_t tmp;

#ifdef ATH_ENABLE_CABQ
	tsf = ah->ah_getTsf64(ah);
	tmp = tsf - sc->sc_swba_tsf;

	if ( tmp > ATH_CABQ_HANDLING_THRESHOLD ) {
		HTC_ReturnBuffers(sc->tgt_htc_handle, EndPt, buf);
		return;
	}

	tgt_HTCRecvMessageHandler(EndPt, hdr_buf, buf, ServiceCtx);
#endif
}
