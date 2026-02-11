hfi1_init_ctxt(struct send_context *sc)
{
	if (sc != NULL) {
		struct hfi1_devdata *dd = sc->dd;
		u64 reg;
		u8 set = (sc->type == SC_USER ?
			  HFI1_CAP_IS_USET(STATIC_RATE_CTRL) :
			  HFI1_CAP_IS_KSET(STATIC_RATE_CTRL));
		reg = read_kctxt_csr(dd, sc->hw_context,
				     SEND_CTXT_CHECK_ENABLE);
		if (set)
			CLEAR_STATIC_RATE_CONTROL_SMASK(reg);
		else
			SET_STATIC_RATE_CONTROL_SMASK(reg);
		write_kctxt_csr(dd, sc->hw_context,
				SEND_CTXT_CHECK_ENABLE, reg);
	}
	return 0;
}
