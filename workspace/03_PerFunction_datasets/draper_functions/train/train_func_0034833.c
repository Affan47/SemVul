niu_device_announce(struct niu *np)
{
	struct net_device *dev = np->dev;

	pr_info("%s: NIU Ethernet %pM\n", dev->name, dev->dev_addr);

	if (np->parent->plat_type == PLAT_TYPE_ATCA_CP3220) {
		pr_info("%s: Port type[%s] mode[%s:%s] XCVR[%s] phy[%s]\n",
				dev->name,
				(np->flags & NIU_FLAGS_XMAC ? "XMAC" : "BMAC"),
				(np->flags & NIU_FLAGS_10G ? "10G" : "1G"),
				(np->flags & NIU_FLAGS_FIBER ? "RGMII FIBER" : "SERDES"),
				(np->mac_xcvr == MAC_XCVR_MII ? "MII" :
				 (np->mac_xcvr == MAC_XCVR_PCS ? "PCS" : "XPCS")),
				np->vpd.phy_type);
	} else {
		pr_info("%s: Port type[%s] mode[%s:%s] XCVR[%s] phy[%s]\n",
				dev->name,
				(np->flags & NIU_FLAGS_XMAC ? "XMAC" : "BMAC"),
				(np->flags & NIU_FLAGS_10G ? "10G" : "1G"),
				(np->flags & NIU_FLAGS_FIBER ? "FIBER" :
				 (np->flags & NIU_FLAGS_XCVR_SERDES ? "SERDES" :
				  "COPPER")),
				(np->mac_xcvr == MAC_XCVR_MII ? "MII" :
				 (np->mac_xcvr == MAC_XCVR_PCS ? "PCS" : "XPCS")),
				np->vpd.phy_type);
	}
}
