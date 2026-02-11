pci_vc_save_restore_dwords(struct pci_dev *dev, int pos,
				       u32 *buf, int dwords, bool save)
{
	int i;

	for (i = 0; i < dwords; i++, buf++) {
		if (save)
			pci_read_config_dword(dev, pos + (i * 4), buf);
		else
			pci_write_config_dword(dev, pos + (i * 4), *buf);
	}
}
