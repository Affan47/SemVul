dwceqos_set_rx_mode(struct net_device *ndev)
{
	struct net_local *lp = netdev_priv(ndev);
	u32 regval = 0;
	u32 mc_filter[2];
	int reg = 1;
	struct netdev_hw_addr *ha;
	unsigned int max_mac_addr;

	max_mac_addr = DWCEQOS_MAX_PERFECT_ADDRESSES(lp->feature1);

	if (ndev->flags & IFF_PROMISC) {
		regval = DWCEQOS_MAC_PKT_FILT_PR;
	} else if (((netdev_mc_count(ndev) > DWCEQOS_HASH_TABLE_SIZE) ||
				(ndev->flags & IFF_ALLMULTI))) {
		regval = DWCEQOS_MAC_PKT_FILT_PM;
		dwceqos_write(lp, REG_DWCEQOS_HASTABLE_LO, 0xffffffff);
		dwceqos_write(lp, REG_DWCEQOS_HASTABLE_HI, 0xffffffff);
	} else if (!netdev_mc_empty(ndev)) {
		regval = DWCEQOS_MAC_PKT_FILT_HMC;
		memset(mc_filter, 0, sizeof(mc_filter));
		netdev_for_each_mc_addr(ha, ndev) {


			int bit_nr = bitrev32(~crc32_le(~0, ha->addr, 6)) >> 26;


			mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
		}
		dwceqos_write(lp, REG_DWCEQOS_HASTABLE_LO, mc_filter[0]);
		dwceqos_write(lp, REG_DWCEQOS_HASTABLE_HI, mc_filter[1]);
	}
	if (netdev_uc_count(ndev) > max_mac_addr) {
		regval |= DWCEQOS_MAC_PKT_FILT_PR;
	} else {
		netdev_for_each_uc_addr(ha, ndev) {
			dwceqos_set_umac_addr(lp, ha->addr, reg);
			reg++;
		}
		for (; reg < DWCEQOS_MAX_PERFECT_ADDRESSES(lp->feature1); reg++)
			dwceqos_disable_umac_addr(lp, reg);
	}
	dwceqos_write(lp, REG_DWCEQOS_MAC_PKT_FILT, regval);
}
