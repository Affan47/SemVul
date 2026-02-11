piix_iocfg_bit18_quirk(struct ata_host *host)
{
	static const struct dmi_system_id sysids[] = {
		{


			.ident = "M570U",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOR, "Clevo Co."),
				DMI_MATCH(DMI_PRODUCT_NAME, "M570U"),
			},
		},

		{ }
	};
	struct pci_dev *pdev = to_pci_dev(host->dev);
	struct piix_host_priv *hpriv = host->private_data;

	if (!dmi_check_system(sysids))
		return;


	if (hpriv->saved_iocfg & (1 << 18)) {
		dev_info(&pdev->dev, "applying IOCFG bit18 quirk\n");
		pci_write_config_dword(pdev, PIIX_IOCFG,
				       hpriv->saved_iocfg & ~(1 << 18));
	}
}
