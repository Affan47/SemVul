mpt_suspend(struct pci_dev *pdev, pm_message_t state)
{
	u32 device_state;
	MPT_ADAPTER *ioc = pci_get_drvdata(pdev);

	device_state = pci_choose_state(pdev, state);
	printk(MYIOC_s_INFO_FMT "pci-suspend: pdev=0x%p, slot=%s, Entering "
	    "operating state [D%d]\n", ioc->name, pdev, pci_name(pdev),
	    device_state);


	if(SendIocReset(ioc, MPI_FUNCTION_IOC_MESSAGE_UNIT_RESET, CAN_SLEEP)) {
		printk(MYIOC_s_ERR_FMT
		"pci-suspend:  IOC msg unit reset failed!\n", ioc->name);
	}


	CHIPREG_WRITE32(&ioc->chip->IntMask, 0xFFFFFFFF);
	ioc->active = 0;


	CHIPREG_WRITE32(&ioc->chip->IntStatus, 0);

	free_irq(ioc->pci_irq, ioc);
	if (ioc->msi_enable)
		pci_disable_msi(ioc->pcidev);
	ioc->pci_irq = -1;
	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_release_selected_regions(pdev, ioc->bars);
	pci_set_power_state(pdev, device_state);
	return 0;
}
