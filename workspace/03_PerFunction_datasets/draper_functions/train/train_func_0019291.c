diva_bri_cleanup_adapter(diva_os_xdi_adapter_t *a)
{
	int i;

	if (a->xdi_adapter.Initialized) {
		diva_bri_stop_adapter(a);
	}


	if (a->xdi_adapter.irq_info.registered) {
		diva_os_remove_irq(a, a->xdi_adapter.irq_info.irq_nr);
	}
	a->xdi_adapter.irq_info.registered = 0;

	if (a->resources.pci.addr[0] && a->resources.pci.bar[0]) {
		divasa_unmap_pci_bar(a->resources.pci.addr[0]);
		a->resources.pci.addr[0] = NULL;
		a->resources.pci.bar[0] = 0;
	}

	for (i = 1; i < 3; i++) {
		if (a->resources.pci.addr[i] && a->resources.pci.bar[i]) {
			diva_os_register_io_port(a, 0,
						 a->resources.pci.bar[i],
						 a->resources.pci.
						 length[i],
						 &a->port_name[0], i);
			a->resources.pci.addr[i] = NULL;
			a->resources.pci.bar[i] = 0;
		}
	}


	diva_os_cancel_soft_isr(&a->xdi_adapter.req_soft_isr);
	diva_os_cancel_soft_isr(&a->xdi_adapter.isr_soft_isr);

	diva_os_remove_soft_isr(&a->xdi_adapter.req_soft_isr);
	a->xdi_adapter.isr_soft_isr.object = NULL;

	diva_os_destroy_spin_lock(&a->xdi_adapter.isr_spin_lock, "rm");
	diva_os_destroy_spin_lock(&a->xdi_adapter.data_spin_lock, "rm");


	if (a->xdi_adapter.e_tbl) {
		diva_os_free(0, a->xdi_adapter.e_tbl);
		a->xdi_adapter.e_tbl = NULL;
	}

	return (0);
}
