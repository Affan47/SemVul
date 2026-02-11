hns_dsaf_tbl_stat_en(struct dsaf_device *dsaf_dev)
{
	u32 o_tbl_ctrl;

	o_tbl_ctrl = dsaf_read_dev(dsaf_dev, DSAF_TBL_DFX_CTRL_0_REG);
	dsaf_set_bit(o_tbl_ctrl, DSAF_TBL_DFX_LINE_LKUP_NUM_EN_S, 1);
	dsaf_set_bit(o_tbl_ctrl, DSAF_TBL_DFX_UC_LKUP_NUM_EN_S, 1);
	dsaf_set_bit(o_tbl_ctrl, DSAF_TBL_DFX_MC_LKUP_NUM_EN_S, 1);
	dsaf_set_bit(o_tbl_ctrl, DSAF_TBL_DFX_BC_LKUP_NUM_EN_S, 1);
	dsaf_write_dev(dsaf_dev, DSAF_TBL_DFX_CTRL_0_REG, o_tbl_ctrl);
}
