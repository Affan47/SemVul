bnx2_set_phys_id(struct net_device *dev, enum ethtool_phys_id_state state)
{
	struct bnx2 *bp = netdev_priv(dev);

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		bp->leds_save = BNX2_RD(bp, BNX2_MISC_CFG);
		BNX2_WR(bp, BNX2_MISC_CFG, BNX2_MISC_CFG_LEDMODE_MAC);
		return 1;

	case ETHTOOL_ID_ON:
		BNX2_WR(bp, BNX2_EMAC_LED, BNX2_EMAC_LED_OVERRIDE |
			BNX2_EMAC_LED_1000MB_OVERRIDE |
			BNX2_EMAC_LED_100MB_OVERRIDE |
			BNX2_EMAC_LED_10MB_OVERRIDE |
			BNX2_EMAC_LED_TRAFFIC_OVERRIDE |
			BNX2_EMAC_LED_TRAFFIC);
		break;

	case ETHTOOL_ID_OFF:
		BNX2_WR(bp, BNX2_EMAC_LED, BNX2_EMAC_LED_OVERRIDE);
		break;

	case ETHTOOL_ID_INACTIVE:
		BNX2_WR(bp, BNX2_EMAC_LED, 0);
		BNX2_WR(bp, BNX2_MISC_CFG, bp->leds_save);
		break;
	}

	return 0;
}
