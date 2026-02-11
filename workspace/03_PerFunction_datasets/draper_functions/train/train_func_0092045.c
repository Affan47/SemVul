bcm_sysport_update_mib_counters(struct bcm_sysport_priv *priv)
{
	int i, j = 0;

	for (i = 0; i < BCM_SYSPORT_STATS_LEN; i++) {
		const struct bcm_sysport_stats *s;
		u8 offset = 0;
		u32 val = 0;
		char *p;

		s = &bcm_sysport_gstrings_stats[i];
		switch (s->type) {
		case BCM_SYSPORT_STAT_NETDEV:
		case BCM_SYSPORT_STAT_SOFT:
			continue;
		case BCM_SYSPORT_STAT_MIB_RX:
		case BCM_SYSPORT_STAT_MIB_TX:
		case BCM_SYSPORT_STAT_RUNT:
			if (s->type != BCM_SYSPORT_STAT_MIB_RX)
				offset = UMAC_MIB_STAT_OFFSET;
			val = umac_readl(priv, UMAC_MIB_START + j + offset);
			break;
		case BCM_SYSPORT_STAT_RXCHK:
			val = rxchk_readl(priv, s->reg_offset);
			if (val == ~0)
				rxchk_writel(priv, 0, s->reg_offset);
			break;
		case BCM_SYSPORT_STAT_RBUF:
			val = rbuf_readl(priv, s->reg_offset);
			if (val == ~0)
				rbuf_writel(priv, 0, s->reg_offset);
			break;
		}

		j += s->stat_sizeof;
		p = (char *)priv + s->stat_offset;
		*(u32 *)p = val;
	}

	netif_dbg(priv, hw, priv->netdev, "updated MIB counters\n");
}
