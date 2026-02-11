t1_interrupts_disable(adapter_t* adapter)
{
	unsigned int i;

	t1_sge_intr_disable(adapter->sge);
	t1_tp_intr_disable(adapter->tp);
	if (adapter->espi)
		t1_espi_intr_disable(adapter->espi);


	for_each_port(adapter, i) {
		adapter->port[i].mac->ops->interrupt_disable(adapter->port[i].mac);
		adapter->port[i].phy->ops->interrupt_disable(adapter->port[i].phy);
	}


	if (t1_is_asic(adapter))
		writel(0, adapter->regs + A_PL_ENABLE);


	pci_write_config_dword(adapter->pdev, A_PCICFG_INTR_ENABLE, 0);

	adapter->slow_intr_mask = 0;
}
