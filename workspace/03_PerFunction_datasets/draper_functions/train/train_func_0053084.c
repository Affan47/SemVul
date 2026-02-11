map_data(const void *data, size_t len, size_t align, int flags)
{
    addr_t start = (flags & MAP_HIGH) ? mboot_high_water_mark : 0x2000;
    addr_t pad = (flags & MAP_NOPAD) ? 0 : -len & (align - 1);
    addr_t xlen = len + pad;

    if (syslinux_memmap_find(amap, SMT_FREE, &start, &xlen, align) ||
	syslinux_add_memmap(&amap, start, len + pad, SMT_ALLOC) ||
	syslinux_add_movelist(&ml, start, (addr_t) data, len) ||
	(pad && syslinux_add_memmap(&mmap, start + len, pad, SMT_ZERO))) {
	printf("Cannot map %zu bytes\n", len + pad);
	return 0;
    }

    dprintf("Mapping 0x%08x bytes (%#x pad) at 0x%08x\n", len, pad, start);

    if (start + len + pad > mboot_high_water_mark)
	mboot_high_water_mark = start + len + pad;

    return start;
}
