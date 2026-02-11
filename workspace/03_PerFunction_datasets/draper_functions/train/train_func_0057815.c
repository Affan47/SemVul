sas_phy_reset(struct sas_phy *phy, int hard_reset)
{
	int ret;
	enum phy_func reset_type;

	if (!phy->enabled)
		return -ENODEV;

	if (hard_reset)
		reset_type = PHY_FUNC_HARD_RESET;
	else
		reset_type = PHY_FUNC_LINK_RESET;

	if (scsi_is_sas_phy_local(phy)) {
		struct Scsi_Host *shost = dev_to_shost(phy->dev.parent);
		struct sas_ha_struct *sas_ha = SHOST_TO_SAS_HA(shost);
		struct asd_sas_phy *asd_phy = sas_ha->sas_phy[phy->number];
		struct sas_internal *i =
			to_sas_internal(sas_ha->core.shost->transportt);

		ret = i->dft->lldd_control_phy(asd_phy, reset_type, NULL);
	} else {
		struct sas_rphy *rphy = dev_to_rphy(phy->dev.parent);
		struct domain_device *ddev = sas_find_dev_by_rphy(rphy);
		ret = sas_smp_phy_control(ddev, phy->number, reset_type, NULL);
	}
	return ret;
}
