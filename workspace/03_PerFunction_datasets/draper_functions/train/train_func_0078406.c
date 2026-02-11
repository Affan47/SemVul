read_aperture(struct pci_dev *dev, u32 *size)
{
	unsigned aper_size = 0, aper_base_32, aper_order;
	u64 aper_base;

	pci_read_config_dword(dev, AMD64_GARTAPERTUREBASE, &aper_base_32);
	pci_read_config_dword(dev, AMD64_GARTAPERTURECTL, &aper_order);
	aper_order = (aper_order >> 1) & 7;

	aper_base = aper_base_32 & 0x7fff;
	aper_base <<= 25;

	aper_size = (32 * 1024 * 1024) << aper_order;
	if (aper_base + aper_size > 0x100000000UL || !aper_size)
		aper_base = 0;

	*size = aper_size;
	return aper_base;
}
