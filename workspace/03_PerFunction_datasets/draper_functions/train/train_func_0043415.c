ixgbe_dcb_unpack_bwgid(struct ixgbe_dcb_config *cfg, int direction,
			    u8 *bwgid)
{
	struct tc_configuration *tc_config = &cfg->tc_config[0];
	int tc;

	for (tc = 0; tc < MAX_TRAFFIC_CLASS; tc++)
		bwgid[tc] = tc_config[tc].path[direction].bwg_id;
}
