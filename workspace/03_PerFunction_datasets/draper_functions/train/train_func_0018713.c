sfi_map_memory(u64 phys, u32 size)
{
	if (!phys || !size)
		return NULL;

	if (sfi_use_ioremap)
		return ioremap_cache(phys, size);
	else
		return early_ioremap(phys, size);
}
