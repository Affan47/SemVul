hns_dsaf_inode_init(struct dsaf_device *dsaf_dev)
{
	u32 reg;
	u32 tc_cfg;
	u32 i;

	if (dsaf_dev->dsaf_tc_mode == HRD_DSAF_4TC_MODE)
		tc_cfg = HNS_DSAF_I4TC_CFG;
	else
		tc_cfg = HNS_DSAF_I8TC_CFG;

	for (i = 0; i < DSAF_INODE_NUM; i++) {
		reg = DSAF_INODE_IN_PORT_NUM_0_REG + 0x80 * i;
		dsaf_set_dev_field(dsaf_dev, reg, DSAF_INODE_IN_PORT_NUM_M,
				   DSAF_INODE_IN_PORT_NUM_S, i % DSAF_XGE_NUM);

		reg = DSAF_INODE_PRI_TC_CFG_0_REG + 0x80 * i;
		dsaf_write_dev(dsaf_dev, reg, tc_cfg);
	}
}
