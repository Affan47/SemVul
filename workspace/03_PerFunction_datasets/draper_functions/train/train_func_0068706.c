tg3_phy_eee_config_ok(struct tg3 *tp)
{
	struct ethtool_eee eee;

	if (!(tp->phy_flags & TG3_PHYFLG_EEE_CAP))
		return true;

	tg3_eee_pull_config(tp, &eee);

	if (tp->eee.eee_enabled) {
		if (tp->eee.advertised != eee.advertised ||
		    tp->eee.tx_lpi_timer != eee.tx_lpi_timer ||
		    tp->eee.tx_lpi_enabled != eee.tx_lpi_enabled)
			return false;
	} else {

		if (eee.advertised)
			return false;
	}

	return true;
}
