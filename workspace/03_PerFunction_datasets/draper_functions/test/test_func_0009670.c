dgap_get_vpd(struct board_t *brd)
{
	u32 magic;
	u32 base_offset;
	u16 rom_offset;
	u16 vpd_offset;
	u16 image_length;
	u16 i;
	u8 byte1;
	u8 byte2;


	magic = FEP5_ROM_MAGIC;
	pci_write_config_dword(brd->pdev, PCI_ROM_ADDRESS, magic);
	pci_read_config_dword(brd->pdev, PCI_ROM_ADDRESS, &magic);


	if (!magic)
		return;


	magic = brd->membase | 0x01;
	pci_write_config_dword(brd->pdev, PCI_ROM_ADDRESS, magic);
	pci_read_config_dword(brd->pdev, PCI_ROM_ADDRESS, &magic);

	byte1 = readb(brd->re_map_membase);
	byte2 = readb(brd->re_map_membase + 1);


	if (byte1 == 0x55 && byte2 == 0xAA) {
		base_offset = 0;


		while (base_offset <= EXPANSION_ROM_SIZE) {


			rom_offset = readw(brd->re_map_membase +
						base_offset + 0x18);
			image_length = readw(brd->re_map_membase +
						rom_offset + 0x10) * 512;
			vpd_offset = readw(brd->re_map_membase +
						rom_offset + 0x08);


			if (vpd_offset)
				break;


			base_offset += image_length;

			byte1 = readb(brd->re_map_membase + base_offset);
			byte2 = readb(brd->re_map_membase + base_offset + 1);


			if (byte1 != 0x55 || byte2 != 0xAA)
				break;
		}


		if (vpd_offset) {
			brd->bd_flags |= BD_HAS_VPD;
			for (i = 0; i < VPDSIZE; i++) {
				brd->vpd[i] = readb(brd->re_map_membase +
							vpd_offset + i);
			}
		}
	}


	magic = FEP5_ROM_MAGIC;
	pci_write_config_dword(brd->pdev, PCI_ROM_ADDRESS, magic);
}
