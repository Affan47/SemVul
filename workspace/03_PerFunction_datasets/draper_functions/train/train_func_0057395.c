rs_set_expected_tpt_table(struct iwl_lq_sta *lq_sta,
				      struct iwl_scale_tbl_info *tbl)
{

	const u16 (*ht_tbl_pointer)[IWL_RATE_COUNT];


	if (WARN_ON_ONCE(!is_legacy(tbl->lq_type) && !is_Ht(tbl->lq_type))) {
		tbl->expected_tpt = expected_tpt_legacy;
		return;
	}


	if (is_legacy(tbl->lq_type)) {
		tbl->expected_tpt = expected_tpt_legacy;
		return;
	}


	if (is_siso(tbl->lq_type) && (!tbl->is_ht40 || lq_sta->is_dup))
		ht_tbl_pointer = expected_tpt_siso20MHz;
	else if (is_siso(tbl->lq_type))
		ht_tbl_pointer = expected_tpt_siso40MHz;
	else if (is_mimo2(tbl->lq_type) && (!tbl->is_ht40 || lq_sta->is_dup))
		ht_tbl_pointer = expected_tpt_mimo2_20MHz;
	else if (is_mimo2(tbl->lq_type))
		ht_tbl_pointer = expected_tpt_mimo2_40MHz;
	else if (is_mimo3(tbl->lq_type) && (!tbl->is_ht40 || lq_sta->is_dup))
		ht_tbl_pointer = expected_tpt_mimo3_20MHz;
	else
		ht_tbl_pointer = expected_tpt_mimo3_40MHz;

	if (!tbl->is_SGI && !lq_sta->is_agg)
		tbl->expected_tpt = ht_tbl_pointer[0];
	else if (tbl->is_SGI && !lq_sta->is_agg)
		tbl->expected_tpt = ht_tbl_pointer[1];
	else if (!tbl->is_SGI && lq_sta->is_agg)
		tbl->expected_tpt = ht_tbl_pointer[2];
	else
		tbl->expected_tpt = ht_tbl_pointer[3];
}
