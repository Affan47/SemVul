set_pio_integrity(struct send_context *sc)
{
	struct hfi1_devdata *dd = sc->dd;
	u64 reg = 0;
	u32 hw_context = sc->hw_context;
	int type = sc->type;


	if (likely(!HFI1_CAP_IS_KSET(NO_INTEGRITY)) &&
	    dd->hfi1_snoop.mode_flag != HFI1_PORT_SNOOP_MODE)
		reg = hfi1_pkt_default_send_ctxt_mask(dd, type);

	write_kctxt_csr(dd, hw_context, SC(CHECK_ENABLE), reg);
}
