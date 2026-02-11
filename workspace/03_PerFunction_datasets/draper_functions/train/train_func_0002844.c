amd8111e_probe_ext_phy(struct amd8111e_priv *lp)
{
	int i;

	lp->ext_phy_id = 0;
	lp->ext_phy_addr = 1;

	for (i = 0x1e; i >= 0; i--) {
		u32 id1, id2;

		if (amd8111e_read_phy(lp, i, MII_PHYSID1, &id1))
			continue;
		if (amd8111e_read_phy(lp, i, MII_PHYSID2, &id2))
			continue;
		lp->ext_phy_id = (id1 << 16) | id2;
		lp->ext_phy_addr = i;
		break;
	}

	if (lp->ext_phy_id)
		printf("Found MII PHY ID 0x%08x at address 0x%02x\n",
		       (unsigned int) lp->ext_phy_id, lp->ext_phy_addr);
	else
		printf("Couldn't detect MII PHY, assuming address 0x01\n");
}
