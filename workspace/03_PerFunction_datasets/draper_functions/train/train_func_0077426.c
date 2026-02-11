smi_init_chipset(void)
{
	uint32_t ret;


	ret = pci_creadl(0, 0, 0, PCI_VID);
	if (ret != ((uint32_t) VID_INTEL | ((uint32_t) DID_82443BX << 16))
	 && ret != ((uint32_t) VID_INTEL | ((uint32_t) DID_82443BX_A << 16))
	 && ret != ((uint32_t) VID_INTEL | ((uint32_t) DID_82443LX << 16))) {
		dprintf("unknown northbridge (vendor 0x%04x, device 0x%04x)\n",
					ret & 0xffff, (ret >> 16) & 0xffff);
		assert(0);
	}

	ret = pci_creadl(0, PIIX_DEV, PIIX_PM_FN, PCI_VID);
	if (ret != ((uint32_t) VID_INTEL | ((uint32_t) DID_PIIX4_PM << 16))) {
		dprintf("unknown southbridge (vendor 0x%04x, device 0x%04x)\n",
				ret & 0xffff, (ret >> 16) & 0xffff);
		assert(0);
	}


	ret = pci_creadl(0, PIIX_DEV, PIIX_PM_FN, PMBA);
	ret &= ~ PMBA_BA_MASK;
	ret |= PM_BASE;
	outl(ret, PCICONF_DATA);


	ret = pci_creadb(0, PIIX_DEV, PIIX_PM_FN, PMREGMISC);
	ret |= PMIOSE;
	pci_cwriteb(0, PIIX_DEV, PIIX_PM_FN, PMREGMISC, ret);
}
