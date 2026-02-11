qlcnic_set_ms_controls(struct qlcnic_adapter *adapter, u64 off,
				   struct qlcnic_ms_reg_ctrl *ms)
{
	ms->control = QLCNIC_MS_CTRL;
	ms->low = QLCNIC_MS_ADDR_LO;
	ms->hi = QLCNIC_MS_ADDR_HI;
	if (off & 0xf) {
		ms->wd[0] = QLCNIC_MS_WRTDATA_LO;
		ms->rd[0] = QLCNIC_MS_RDDATA_LO;
		ms->wd[1] = QLCNIC_MS_WRTDATA_HI;
		ms->rd[1] = QLCNIC_MS_RDDATA_HI;
		ms->wd[2] = QLCNIC_MS_WRTDATA_ULO;
		ms->wd[3] = QLCNIC_MS_WRTDATA_UHI;
		ms->rd[2] = QLCNIC_MS_RDDATA_ULO;
		ms->rd[3] = QLCNIC_MS_RDDATA_UHI;
	} else {
		ms->wd[0] = QLCNIC_MS_WRTDATA_ULO;
		ms->rd[0] = QLCNIC_MS_RDDATA_ULO;
		ms->wd[1] = QLCNIC_MS_WRTDATA_UHI;
		ms->rd[1] = QLCNIC_MS_RDDATA_UHI;
		ms->wd[2] = QLCNIC_MS_WRTDATA_LO;
		ms->wd[3] = QLCNIC_MS_WRTDATA_HI;
		ms->rd[2] = QLCNIC_MS_RDDATA_LO;
		ms->rd[3] = QLCNIC_MS_RDDATA_HI;
	}

	ms->ocm_window = OCM_WIN_P3P(off);
	ms->off = GET_MEM_OFFS_2M(off);
}
