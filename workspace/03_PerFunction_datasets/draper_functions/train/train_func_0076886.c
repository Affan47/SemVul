ath_hal_reg_rmw_tgt(void *Context, A_UINT16 Command,
				A_UINT16 SeqNo, A_UINT8 *data,
				a_int32_t datalen)
{
	struct ath_softc_tgt *sc = (struct ath_softc_tgt *)Context;
	struct ath_hal *ah = sc->sc_ah;
	struct register_rmw *buf = (struct register_rmw *)data;
	int i;

	for (i = 0; i < datalen;
	     i += sizeof(struct register_rmw)) {
		a_uint32_t val;
		buf = (struct register_rmw *)(data + i);

		val = ath_reg_read_filter(ah, buf->reg);
		val &= ~buf->clr;
		val |= buf->set;
		ath_hal_reg_write_filter(ah, buf->reg, val);
	}
	wmi_cmd_rsp(sc->tgt_wmi_handle, Command, SeqNo, NULL, 0);
}
