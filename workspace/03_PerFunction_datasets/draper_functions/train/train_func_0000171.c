wlc_phy_stf_chain_set(struct brcms_phy_pub *pih, u8 txchain, u8 rxchain)
{
	struct brcms_phy *pi = container_of(pih, struct brcms_phy, pubpi_ro);

	pi->sh->phytxchain = txchain;

	if (ISNPHY(pi))
		wlc_phy_rxcore_setstate_nphy(pih, rxchain);

	pi->pubpi.phy_corenum = (u8)hweight8(pi->sh->phyrxchain);
}
