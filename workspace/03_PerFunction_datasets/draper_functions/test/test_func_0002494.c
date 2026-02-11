hrtmon_map_banks (void)
{
	uaecptr addr;

	if (!hrtmemory)
		return;

	addr = hrtmem_start;
	while (addr != hrtmem_end) {
		map_banks (&hrtmem_bank, addr >> 16, hrtmem_size >> 16, 0);
		addr += hrtmem_size;
		if (!hrtmem_end)
			break;
	}
	if (hrtmem2_size) {
		addr = hrtmem2_start;
		while (addr != hrtmem2_end) {
			map_banks (&hrtmem2_bank, addr >> 16, hrtmem2_size2 >> 16, 0);
			addr += hrtmem2_size;
			if (!hrtmem2_end)
				break;
		}
	}
	if (hrtmem3_size)
		map_banks (&hrtmem3_bank, hrtmem3_start >> 16, hrtmem3_size >> 16, 0);
}
