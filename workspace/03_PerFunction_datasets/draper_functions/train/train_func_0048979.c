ems_pci_del_card(struct pci_dev *pdev)
{
	struct ems_pci_card *card = pci_get_drvdata(pdev);
	struct net_device *dev;
	int i = 0;

	for (i = 0; i < card->channels; i++) {
		dev = card->net_dev[i];

		if (!dev)
			continue;

		dev_info(&pdev->dev, "Removing %s.\n", dev->name);
		unregister_sja1000dev(dev);
		free_sja1000dev(dev);
	}

	if (card->base_addr != NULL)
		pci_iounmap(card->pci_dev, card->base_addr);

	if (card->conf_addr != NULL)
		pci_iounmap(card->pci_dev, card->conf_addr);

	kfree(card);

	pci_disable_device(pdev);
}
