efi_memmap_init(void)
{
	if (efi_enabled(EFI_PARAVIRT))
		return 0;


	memmap.map = early_memremap((unsigned long)memmap.phys_map,
				   memmap.nr_map * memmap.desc_size);
	if (memmap.map == NULL) {
		pr_err("Could not map the memory map!\n");
		return -ENOMEM;
	}
	memmap.map_end = memmap.map + (memmap.nr_map * memmap.desc_size);

	if (add_efi_memmap)
		do_add_efi_memmap();

	set_bit(EFI_MEMMAP, &efi.flags);

	return 0;
}
