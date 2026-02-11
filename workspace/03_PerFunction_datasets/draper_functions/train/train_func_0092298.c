dump_pci(struct upload_backend *be)
{
    int cfgtype;
    unsigned int nbus, ndev, nfunc, maxfunc;
    pciaddr_t a;
    uint32_t did;
    uint8_t hdrtype;

    cfgtype = pci_set_config_type(PCI_CFG_AUTO);
    if (cfgtype == PCI_CFG_NONE)
	return;

    cpio_mkdir(be, "pci");

    for (nbus = 0; nbus < MAX_PCI_BUSES; nbus++) {
	for (ndev = 0; ndev < MAX_PCI_DEVICES; ndev++) {
	    maxfunc = 1;

	    for (nfunc = 0; nfunc < maxfunc; nfunc++) {
		a = pci_mkaddr(nbus, ndev, nfunc, 0);
		did = pci_readl(a);

		if (did == 0xffffffff || did == 0xffff0000 ||
		    did == 0x0000ffff || did == 0x00000000)
		    continue;

		hdrtype = pci_readb(a + 0x0e);
		if (hdrtype & 0x80)
		    maxfunc = MAX_PCI_FUNC;

		dump_pci_device(be, a, hdrtype);
	    }
	}
    }

    printf("Scanning PCI bus... done.  \n");
}
