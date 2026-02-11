broadwell_mci_bind_devs(struct mem_ctl_info *mci,
				 struct sbridge_dev *sbridge_dev)
{
	struct sbridge_pvt *pvt = mci->pvt_info;
	struct pci_dev *pdev;
	u8 saw_chan_mask = 0;
	int i;


	if (pvt->info.pci_vtd == NULL)

		pvt->info.pci_vtd = pci_get_device(PCI_VENDOR_ID_INTEL,
						   PCI_DEVICE_ID_INTEL_BROADWELL_IMC_VTD_MISC,
						   NULL);

	for (i = 0; i < sbridge_dev->n_devs; i++) {
		pdev = sbridge_dev->pdev[i];
		if (!pdev)
			continue;

		switch (pdev->device) {
		case PCI_DEVICE_ID_INTEL_BROADWELL_IMC_CBO_SAD0:
			pvt->pci_sad0 = pdev;
			break;
		case PCI_DEVICE_ID_INTEL_BROADWELL_IMC_CBO_SAD1:
			pvt->pci_sad1 = pdev;
			break;
		case PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0:
			pvt->pci_ha0 = pdev;
			break;
		case PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TA:
			pvt->pci_ta = pdev;
			break;
		case PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_THERMAL:
			pvt->pci_ras = pdev;
			break;
		case PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TAD0:
		case PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TAD1:
		case PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TAD2:
		case PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TAD3:
		{
			int id = pdev->device - PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA0_TAD0;
			pvt->pci_tad[id] = pdev;
			saw_chan_mask |= 1 << id;
		}
			break;
		case PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TAD0:
		case PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TAD1:
		case PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TAD2:
		case PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TAD3:
		{
			int id = pdev->device - PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TAD0 + 4;
			pvt->pci_tad[id] = pdev;
			saw_chan_mask |= 1 << id;
		}
			break;
		case PCI_DEVICE_ID_INTEL_BROADWELL_IMC_DDRIO0:
			pvt->pci_ddrio = pdev;
			break;
		case PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1:
			pvt->pci_ha1 = pdev;
			break;
		case PCI_DEVICE_ID_INTEL_BROADWELL_IMC_HA1_TA:
			pvt->pci_ha1_ta = pdev;
			break;
		default:
			break;
		}

		edac_dbg(0, "Associated PCI %02x.%02d.%d with dev = %p\n",
			 sbridge_dev->bus,
			 PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn),
			 pdev);
	}


	if (!pvt->pci_sad0 || !pvt->pci_ha0 || !pvt->pci_sad1 ||
	    !pvt->pci_ras  || !pvt->pci_ta || !pvt->info.pci_vtd)
		goto enodev;

	if (saw_chan_mask != 0x0f &&
	    saw_chan_mask != 0x33 &&
	    saw_chan_mask != 0xff)
		goto enodev;
	return 0;

enodev:
	sbridge_printk(KERN_ERR, "Some needed devices are missing\n");
	return -ENODEV;
}
