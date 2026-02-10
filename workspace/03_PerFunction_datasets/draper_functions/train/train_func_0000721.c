jme_check_link(struct net_device *netdev, int testonly)
{
	struct jme_adapter *jme = netdev->priv;
	u32 phylink, ghc, cnt = JME_SPDRSV_TIMEOUT, gpreg1;
	int rc = 0;

	phylink = jread32(jme, JME_PHY_LINK);

	if (phylink & PHY_LINK_UP) {


		while (!(phylink & PHY_LINK_SPEEDDPU_RESOLVED) &&
			--cnt) {

			udelay(1);
			phylink = jread32(jme, JME_PHY_LINK);
		}
		if (!cnt)
			DBG("Waiting speed resolve timeout.\n");

		if (jme->phylink == phylink) {
			rc = 1;
			goto out;
		}
		if (testonly)
			goto out;

		jme->phylink = phylink;

		ghc = jme->reg_ghc & ~(GHC_SPEED | GHC_DPX |
				GHC_TO_CLK_PCIE | GHC_TXMAC_CLK_PCIE |
				GHC_TO_CLK_GPHY | GHC_TXMAC_CLK_GPHY);
		switch (phylink & PHY_LINK_SPEED_MASK) {
		case PHY_LINK_SPEED_10M:
			ghc |= GHC_SPEED_10M |
				GHC_TO_CLK_PCIE | GHC_TXMAC_CLK_PCIE;
			break;
		case PHY_LINK_SPEED_100M:
			ghc |= GHC_SPEED_100M |
				GHC_TO_CLK_PCIE | GHC_TXMAC_CLK_PCIE;
			break;
		case PHY_LINK_SPEED_1000M:
			ghc |= GHC_SPEED_1000M |
				GHC_TO_CLK_GPHY | GHC_TXMAC_CLK_GPHY;
			break;
		default:
			break;
		}

		if (phylink & PHY_LINK_DUPLEX) {
			jwrite32(jme, JME_TXMCS, TXMCS_DEFAULT);
			ghc |= GHC_DPX;
		} else {
			jwrite32(jme, JME_TXMCS, TXMCS_DEFAULT |
						TXMCS_BACKOFF |
						TXMCS_CARRIERSENSE |
						TXMCS_COLLISION);
			jwrite32(jme, JME_TXTRHD, TXTRHD_TXPEN |
				((0x2000 << TXTRHD_TXP_SHIFT) & TXTRHD_TXP) |
				TXTRHD_TXREN |
				((8 << TXTRHD_TXRL_SHIFT) & TXTRHD_TXRL));
		}

		gpreg1 = GPREG1_DEFAULT;
		if (is_buggy250(jme->pdev->device, jme->chiprev)) {
			if (!(phylink & PHY_LINK_DUPLEX))
				gpreg1 |= GPREG1_HALFMODEPATCH;
			switch (phylink & PHY_LINK_SPEED_MASK) {
			case PHY_LINK_SPEED_10M:
				jme_set_phyfifoa(jme);
				gpreg1 |= GPREG1_RSSPATCH;
				break;
			case PHY_LINK_SPEED_100M:
				jme_set_phyfifob(jme);
				gpreg1 |= GPREG1_RSSPATCH;
				break;
			case PHY_LINK_SPEED_1000M:
				jme_set_phyfifoa(jme);
				break;
			default:
				break;
			}
		}

		jwrite32(jme, JME_GPREG1, gpreg1);
		jwrite32(jme, JME_GHC, ghc);
		jme->reg_ghc = ghc;

		DBG("Link is up at %d Mbps, %s-Duplex, MDI%s.\n",
		    ((phylink & PHY_LINK_SPEED_MASK)
			     == PHY_LINK_SPEED_1000M) ? 1000 :
		    ((phylink & PHY_LINK_SPEED_MASK)
			     == PHY_LINK_SPEED_100M)  ? 100  : 10,
		    (phylink & PHY_LINK_DUPLEX) ? "Full" : "Half",
		    (phylink & PHY_LINK_MDI_STAT) ? "-X" : "");
		netdev_link_up(netdev);
	} else {
		if (testonly)
			goto out;

		DBG("Link is down.\n");
		jme->phylink = 0;
		netdev_link_down(netdev);
	}

out:
	return rc;
}
