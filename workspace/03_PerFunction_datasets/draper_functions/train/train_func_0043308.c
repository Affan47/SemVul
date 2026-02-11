se200pci_WM8776_set_agc(struct snd_ice1712 *ice, unsigned int agc)
{

	switch (agc) {
	case 0:
		se200pci_WM8776_write(ice, 0x11, 0x000);
		break;
	case 1:
		se200pci_WM8776_write(ice, 0x10, 0x07b);
		se200pci_WM8776_write(ice, 0x11, 0x100);
		break;
	case 2:
		se200pci_WM8776_write(ice, 0x10, 0x1fb);
		se200pci_WM8776_write(ice, 0x11, 0x100);
		break;
	}
}
