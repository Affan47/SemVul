fill_e820map(boot_params_t *bp, mmap_desc_t *mdesc)
{
	int nr_map, e820_nr_map = 0, i;
	UINT64 start, end, size;
	EFI_MEMORY_DESCRIPTOR	*md, *p;
	struct e820entry *e820_map;

	nr_map = mdesc->map_size/mdesc->desc_size;
	e820_map = (struct e820entry *)bp->s.e820_map;

	for (i = 0, p = mdesc->md; i < nr_map; i++)
	{
		md = p;
		switch (md->Type) {
		case EfiACPIReclaimMemory:
			add_memory_region(e820_map, &e820_nr_map,
					  md->PhysicalStart,
					  md->NumberOfPages << EFI_PAGE_SHIFT,
					  E820_ACPI);
			break;
		case EfiRuntimeServicesCode:
			add_memory_region(e820_map, &e820_nr_map,
					  md->PhysicalStart,
					  md->NumberOfPages << EFI_PAGE_SHIFT,
					  E820_EXEC_CODE);
			break;
		case EfiRuntimeServicesData:
		case EfiReservedMemoryType:
		case EfiMemoryMappedIO:
		case EfiMemoryMappedIOPortSpace:
		case EfiUnusableMemory:
		case EfiPalCode:
			add_memory_region(e820_map, &e820_nr_map,
					  md->PhysicalStart,
					  md->NumberOfPages << EFI_PAGE_SHIFT,
					  E820_RESERVED);
			break;
		case EfiLoaderCode:
		case EfiLoaderData:
		case EfiBootServicesCode:
		case EfiBootServicesData:
		case EfiConventionalMemory:
			start = md->PhysicalStart;
			size = md->NumberOfPages << EFI_PAGE_SHIFT;
			end = start + size;

			if (start < 0x100000ULL && end > 0xA0000ULL) {
				if (start < 0xA0000ULL) {


					add_memory_region(e820_map,
							  &e820_nr_map,
							  start,
							  0xA0000ULL-start,
							  E820_RAM);
				}
				if (end <= 0x100000ULL)
					continue;


				start = 0x100000ULL;
				size = end - start;
			}
			add_memory_region(e820_map, &e820_nr_map,
					  start, size, E820_RAM);
			break;
		case EfiACPIMemoryNVS:
			add_memory_region(e820_map, &e820_nr_map,
					  md->PhysicalStart,
					  md->NumberOfPages << EFI_PAGE_SHIFT,
					  E820_NVS);
			break;
		default:

			DBG_PRT((L"hit default!?"));
			add_memory_region(e820_map, &e820_nr_map,
					  md->PhysicalStart,
					  md->NumberOfPages << EFI_PAGE_SHIFT,
					  E820_RESERVED);
			break;
		}
		p = NextMemoryDescriptor(p, mdesc->desc_size);
	}
	bp->s.e820_nrmap = e820_nr_map;
}
