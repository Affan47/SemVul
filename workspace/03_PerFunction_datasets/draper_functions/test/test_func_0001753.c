mwifiex_pcie_cleanup(struct mwifiex_adapter *adapter)
{
	struct pcie_service_card *card = adapter->card;
	struct pci_dev *pdev = card->dev;
	const struct mwifiex_pcie_card_reg *reg = card->pcie.reg;

	if (user_rmmod) {
		mwifiex_dbg(adapter, INFO,
			    "Clearing driver ready signature\n");
		if (mwifiex_write_reg(adapter, reg->drv_rdy, 0x00000000))
			mwifiex_dbg(adapter, ERROR,
				    "Failed to write driver not-ready signature\n");
	}

	if (pdev) {
		pci_iounmap(pdev, card->pci_mmap);
		pci_iounmap(pdev, card->pci_mmap1);
		pci_disable_device(pdev);
		pci_release_region(pdev, 2);
		pci_release_region(pdev, 0);
		pci_set_drvdata(pdev, NULL);
	}
	kfree(card);
}
