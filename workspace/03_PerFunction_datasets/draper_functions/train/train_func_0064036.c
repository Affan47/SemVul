qlcnic_dcb_fill_cee_pg_params(struct qlcnic_dcb_param *each,
					  struct qlcnic_dcb_cee *type)
{
	struct qlcnic_dcb_pg_cfg *pg_cfg;
	u8 i, tsa, bw_per;

	for (i = 0; i < QLC_DCB_MAX_PG; i++) {
		pg_cfg = &type->pg_cfg[i];
		pg_cfg->valid = true;

		if (i < 4) {
			bw_per = QLC_DCB_GET_BWPER_PG(each->pg_bw_map[0], i);
			tsa = QLC_DCB_GET_TSA_PG(each->pg_tsa_map[0], i);
		} else {
			bw_per = QLC_DCB_GET_BWPER_PG(each->pg_bw_map[1], i);
			tsa = QLC_DCB_GET_TSA_PG(each->pg_tsa_map[1], i);
		}

		pg_cfg->total_bw_percent = bw_per;
		pg_cfg->tsa_type = tsa;
	}
}
