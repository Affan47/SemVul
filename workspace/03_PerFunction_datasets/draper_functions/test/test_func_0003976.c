ord_phy(struct asd_ha_struct *asd_ha, struct asd_phy *phy)
{
	u8 enabled_mask = asd_ha->hw_prof.enabled_phys;
	int i, k = 0;

	for_each_phy(enabled_mask, enabled_mask, i) {
		if (&asd_ha->phys[i] == phy)
			return k;
		k++;
	}
	return 0;
}
