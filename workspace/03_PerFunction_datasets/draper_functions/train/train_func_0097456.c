mei_me_quirk_probe(struct pci_dev *pdev,
				const struct mei_cfg *cfg)
{
	if (cfg->quirk_probe && cfg->quirk_probe(pdev)) {
		dev_info(&pdev->dev, "Device doesn't have valid ME Interface\n");
		return false;
	}

	return true;
}
