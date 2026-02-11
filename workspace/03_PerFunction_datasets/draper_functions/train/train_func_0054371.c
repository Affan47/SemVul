divas_create_pci_card(int handle, void *pci_dev_handle)
{
	diva_supported_cards_info_t *pI = &divas_supported_cards[handle];
	diva_os_spin_lock_magic_t old_irql;
	diva_os_xdi_adapter_t *a;

	DBG_LOG(("found %d-%s", pI->CardOrdinal, CardProperties[pI->CardOrdinal].Name))

		if (!(a = (diva_os_xdi_adapter_t *) diva_os_malloc(0, sizeof(*a)))) {
			DBG_ERR(("A: can't alloc adapter"));
			return NULL;
		}

	memset(a, 0x00, sizeof(*a));

	a->CardIndex = handle;
	a->CardOrdinal = pI->CardOrdinal;
	a->Bus = DIVAS_XDI_ADAPTER_BUS_PCI;
	a->xdi_adapter.cardType = a->CardOrdinal;
	a->resources.pci.bus = diva_os_get_pci_bus(pci_dev_handle);
	a->resources.pci.func = diva_os_get_pci_func(pci_dev_handle);
	a->resources.pci.hdev = pci_dev_handle;


	diva_os_enter_spin_lock(&adapter_lock, &old_irql, "found_pci_card");
	list_add_tail(&a->link, &adapter_queue);
	diva_os_leave_spin_lock(&adapter_lock, &old_irql, "found_pci_card");

	if ((*(pI->init_card)) (a)) {
		diva_os_enter_spin_lock(&adapter_lock, &old_irql, "found_pci_card");
		list_del(&a->link);
		diva_os_leave_spin_lock(&adapter_lock, &old_irql, "found_pci_card");
		diva_os_free(0, a);
		DBG_ERR(("A: can't get adapter resources"));
		return NULL;
	}

	return (a);
}
