gru_get_cb_exception_detail(void *cb,
		struct control_block_extended_exc_detail *excdet)
{
	struct gru_control_block_extended *cbe;
	struct gru_thread_state *kgts = NULL;
	unsigned long off;
	int cbrnum, bid;


	for_each_possible_blade(bid) {
		if (!gru_base[bid])
			break;
		kgts = gru_base[bid]->bs_kgts;
		if (!kgts || !kgts->ts_gru)
			continue;
		off = cb - kgts->ts_gru->gs_gru_base_vaddr;
		if (off < GRU_SIZE)
			break;
		kgts = NULL;
	}
	BUG_ON(!kgts);
	cbrnum = thread_cbr_number(kgts, get_cb_number(cb));
	cbe = get_cbe(GRUBASE(cb), cbrnum);
	gru_flush_cache(cbe);
	sync_core();
	excdet->opc = cbe->opccpy;
	excdet->exopc = cbe->exopccpy;
	excdet->ecause = cbe->ecause;
	excdet->exceptdet0 = cbe->idef1upd;
	excdet->exceptdet1 = cbe->idef3upd;
	gru_flush_cache(cbe);
	return 0;
}
