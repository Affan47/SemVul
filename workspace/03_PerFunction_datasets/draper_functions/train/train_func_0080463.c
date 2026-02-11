sas_phy_setup(struct transport_container *tc, struct device *dev,
			 struct device *cdev)
{
	struct sas_phy *phy = dev_to_phy(dev);
	struct Scsi_Host *shost = dev_to_shost(phy->dev.parent);
	struct sas_internal *i = to_sas_internal(shost->transportt);

	if (i->f->phy_setup)
		i->f->phy_setup(phy);

	return 0;
}
