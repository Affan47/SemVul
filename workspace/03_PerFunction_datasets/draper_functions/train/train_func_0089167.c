mwifiex_pcie_interrupt(int irq, void *context)
{
	struct pci_dev *pdev = (struct pci_dev *)context;
	struct pcie_service_card *card;
	struct mwifiex_adapter *adapter;

	if (!pdev) {
		pr_debug("info: %s: pdev is NULL\n", (u8 *)pdev);
		goto exit;
	}

	card = pci_get_drvdata(pdev);
	if (!card || !card->adapter) {
		pr_debug("info: %s: card=%p adapter=%p\n", __func__, card,
			 card ? card->adapter : NULL);
		goto exit;
	}
	adapter = card->adapter;

	if (adapter->surprise_removed)
		goto exit;

	mwifiex_interrupt_status(adapter);
	mwifiex_queue_main_work(adapter);

exit:
	return IRQ_HANDLED;
}
