bnx2x_init_rss(struct bnx2x *bp)
{
	int i;
	u8 num_eth_queues = BNX2X_NUM_ETH_QUEUES(bp);


	for (i = 0; i < sizeof(bp->rss_conf_obj.ind_table); i++)
		bp->rss_conf_obj.ind_table[i] =
			bp->fp->cl_id +
			ethtool_rxfh_indir_default(i, num_eth_queues);


	return bnx2x_config_rss_eth(bp, bp->port.pmf || !CHIP_IS_E1x(bp));
}
