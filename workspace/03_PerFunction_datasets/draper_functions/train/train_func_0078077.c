at76_dump_mib_mdomain(struct at76_priv *priv)
{
	int ret;
	struct mib_mdomain *m = kmalloc(sizeof(struct mib_mdomain), GFP_KERNEL);

	if (!m)
		return;

	ret = at76_get_mib(priv->udev, MIB_MDOMAIN, m,
			   sizeof(struct mib_mdomain));
	if (ret < 0) {
		wiphy_err(priv->hw->wiphy,
			  "at76_get_mib (MDOMAIN) failed: %d\n", ret);
		goto exit;
	}

	at76_dbg(DBG_MIB, "%s: MIB MDOMAIN: channel_list %*phD",
		 wiphy_name(priv->hw->wiphy),
		 (int)sizeof(m->channel_list), m->channel_list);

	at76_dbg(DBG_MIB, "%s: MIB MDOMAIN: tx_powerlevel %*phD",
		 wiphy_name(priv->hw->wiphy),
		 (int)sizeof(m->tx_powerlevel), m->tx_powerlevel);
exit:
	kfree(m);
}
