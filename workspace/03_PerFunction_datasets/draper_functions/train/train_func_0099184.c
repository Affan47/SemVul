qlafx00_iospace_config(struct qla_hw_data *ha)
{
	if (pci_request_selected_regions(ha->pdev, ha->bars,
	    QLA2XXX_DRIVER_NAME)) {
		ql_log_pci(ql_log_fatal, ha->pdev, 0x014e,
		    "Failed to reserve PIO/MMIO regions (%s), aborting.\n",
		    pci_name(ha->pdev));
		goto iospace_error_exit;
	}


	if (!(pci_resource_flags(ha->pdev, 0) & IORESOURCE_MEM)) {
		ql_log_pci(ql_log_warn, ha->pdev, 0x014f,
		    "Invalid pci I/O region size (%s).\n",
		    pci_name(ha->pdev));
		goto iospace_error_exit;
	}
	if (pci_resource_len(ha->pdev, 0) < BAR0_LEN_FX00) {
		ql_log_pci(ql_log_warn, ha->pdev, 0x0127,
		    "Invalid PCI mem BAR0 region size (%s), aborting\n",
			pci_name(ha->pdev));
		goto iospace_error_exit;
	}

	ha->cregbase =
	    ioremap_nocache(pci_resource_start(ha->pdev, 0), BAR0_LEN_FX00);
	if (!ha->cregbase) {
		ql_log_pci(ql_log_fatal, ha->pdev, 0x0128,
		    "cannot remap MMIO (%s), aborting\n", pci_name(ha->pdev));
		goto iospace_error_exit;
	}

	if (!(pci_resource_flags(ha->pdev, 2) & IORESOURCE_MEM)) {
		ql_log_pci(ql_log_warn, ha->pdev, 0x0129,
		    "region #2 not an MMIO resource (%s), aborting\n",
		    pci_name(ha->pdev));
		goto iospace_error_exit;
	}
	if (pci_resource_len(ha->pdev, 2) < BAR2_LEN_FX00) {
		ql_log_pci(ql_log_warn, ha->pdev, 0x012a,
		    "Invalid PCI mem BAR2 region size (%s), aborting\n",
			pci_name(ha->pdev));
		goto iospace_error_exit;
	}

	ha->iobase =
	    ioremap_nocache(pci_resource_start(ha->pdev, 2), BAR2_LEN_FX00);
	if (!ha->iobase) {
		ql_log_pci(ql_log_fatal, ha->pdev, 0x012b,
		    "cannot remap MMIO (%s), aborting\n", pci_name(ha->pdev));
		goto iospace_error_exit;
	}


	ha->max_req_queues = ha->max_rsp_queues = 1;

	ql_log_pci(ql_log_info, ha->pdev, 0x012c,
	    "Bars 0x%x, iobase0 0x%p, iobase2 0x%p\n",
	    ha->bars, ha->cregbase, ha->iobase);

	return 0;

iospace_error_exit:
	return -ENOMEM;
}
