ld10k1_tram_res_alloc_hwacc(ld10k1_dsp_mgr_t *dsp_mgr, ld10k1_dsp_tram_resolve_t *res)
{
	int i, j;
	int grp_idx;
	int hwacc;


	for (i = 0; i < res->item_count; i++) {
		grp_idx = res->items[i].grp_idx;
		if (dsp_mgr->tram_grp[grp_idx].pos != TRAM_POS_NONE &&
			dsp_mgr->tram_grp[grp_idx].pos != res->items[i].pos) {
			for (j = 0; j < dsp_mgr->max_tram_acc; j++)
				if (dsp_mgr->tram_acc[j].used &&
					dsp_mgr->tram_acc[j].grp == grp_idx)
					ld10k1_tram_hwacc_free(dsp_mgr, dsp_mgr->tram_acc[j].hwacc);
			dsp_mgr->tram_grp[grp_idx].pos = TRAM_POS_NONE;
		}
	}


	for (i = 0; i < res->item_count; i++) {
		grp_idx = res->items[i].grp_idx;
		if (dsp_mgr->tram_grp[grp_idx].pos == TRAM_POS_NONE &&
			dsp_mgr->tram_grp[grp_idx].pos != res->items[i].pos) {
			dsp_mgr->tram_grp[grp_idx].pos = res->items[i].pos;
			for (j = 0; j < dsp_mgr->max_tram_acc; j++)
				if (dsp_mgr->tram_acc[j].used &&
					dsp_mgr->tram_acc[j].grp == grp_idx) {
					hwacc = ld10k1_tram_hwacc_alloc(dsp_mgr, res->items[i].pos == TRAM_POS_EXTERNAL ? 1 : 0);
					dsp_mgr->tram_acc[j].hwacc = hwacc;
				}
		}
	}
	return 0;
}
