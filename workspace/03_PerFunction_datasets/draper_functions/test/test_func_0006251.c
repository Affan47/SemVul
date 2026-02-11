sisfb_find_rom(struct pci_dev *pdev)
{
	struct sis_video_info *ivideo = pci_get_drvdata(pdev);
	void __iomem *rom_base;
	unsigned char *myrombase = NULL;
	size_t romsize;


	if(!ivideo->nbridge) {

		if((rom_base = pci_map_rom(pdev, &romsize))) {

			if(sisfb_check_rom(rom_base, ivideo)) {

				if((myrombase = vmalloc(65536))) {
					memcpy_fromio(myrombase, rom_base,
							(romsize > 65536) ? 65536 : romsize);
				}
			}
			pci_unmap_rom(pdev, rom_base);
		}
	}

	if(myrombase) return myrombase;


#if defined(__i386__) || defined(__x86_64__)
	{
		u32 temp;

		for (temp = 0x000c0000; temp < 0x000f0000; temp += 0x00001000) {

			rom_base = ioremap(temp, 65536);
			if (!rom_base)
				continue;

			if (!sisfb_check_rom(rom_base, ivideo)) {
				iounmap(rom_base);
				continue;
			}

			if ((myrombase = vmalloc(65536)))
				memcpy_fromio(myrombase, rom_base, 65536);

			iounmap(rom_base);
			break;

		}

	}
#endif

	return myrombase;
}
