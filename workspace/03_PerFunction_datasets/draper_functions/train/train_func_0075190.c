qlcnic_dcb_fill_cee_tc_params(struct qlcnic_dcb_mbx_params *mbx,
					  struct qlcnic_dcb_param *each,
					  struct qlcnic_dcb_cee *type)
{
	struct qlcnic_dcb_tc_cfg *tc_cfg;
	u8 i, tc, pgid;

	for (i = 0; i < QLC_DCB_MAX_PRIO; i++) {
		tc = QLC_DCB_GET_TC_PRIO(mbx->prio_tc_map, i);
		tc_cfg = &type->tc_cfg[tc];
		tc_cfg->valid = true;
		tc_cfg->up_tc_map |= QLC_DCB_GET_MAP(i);

		if (QLC_DCB_GET_PFC_PRIO(each->hdr_prio_pfc_map[1], i) &&
		    type->pfc_mode_enable) {
			tc_cfg->prio_cfg[i].valid = true;
			tc_cfg->prio_cfg[i].pfc_type = QLC_PFC_FULL;
		}

		if (i < 4)
			pgid = QLC_DCB_GET_PGID_PRIO(each->prio_pg_map[0], i);
		else
			pgid = QLC_DCB_GET_PGID_PRIO(each->prio_pg_map[1], i);

		tc_cfg->pgid = pgid;

		tc_cfg->prio_type = QLC_PRIO_LINK;
		type->pg_cfg[tc_cfg->pgid].prio_count++;
	}
}
