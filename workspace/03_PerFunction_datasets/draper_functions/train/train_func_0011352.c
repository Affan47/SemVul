sh_eth_tsu_disable_cam_entry_table(struct net_device *ndev,
					      int entry)
{
	struct sh_eth_private *mdp = netdev_priv(ndev);
	void *reg_offset = sh_eth_tsu_get_offset(mdp, TSU_ADRH0);
	int ret;
	u8 blank[ETH_ALEN];

	sh_eth_tsu_write(mdp, sh_eth_tsu_read(mdp, TSU_TEN) &
			 ~(1 << (31 - entry)), TSU_TEN);

	memset(blank, 0, sizeof(blank));
	ret = sh_eth_tsu_write_entry(ndev, reg_offset + entry * 8, blank);
	if (ret < 0)
		return ret;
	return 0;
}
