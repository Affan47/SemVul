early_init_fdt_scan_reserved_mem(void)
{
	int n;
	u64 base, size;

	if (!initial_boot_params)
		return;


	for (n = 0; ; n++) {
		fdt_get_mem_rsv(initial_boot_params, n, &base, &size);
		if (!size)
			break;
		early_init_dt_reserve_memory_arch(base, size, 0);
	}

	of_scan_flat_dt(__fdt_scan_reserved_mem, NULL);
	fdt_init_reserved_mem();
}
