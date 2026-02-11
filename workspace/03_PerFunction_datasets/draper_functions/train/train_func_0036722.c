cxgb_down(struct adapter *adapter)
{
	t1_sge_stop(adapter->sge);
	t1_interrupts_disable(adapter);
	free_irq(adapter->pdev->irq, adapter);
	if (adapter->params.has_msi)
		pci_disable_msi(adapter->pdev);
}
