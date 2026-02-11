sfi_map_table(u64 pa)
{
	struct sfi_table_header *th;
	u32 length;

	if (!TABLE_ON_PAGE(syst_pa, pa, sizeof(struct sfi_table_header)))
		th = sfi_map_memory(pa, sizeof(struct sfi_table_header));
	else
		th = (void *)syst_va + (pa - syst_pa);


	if (TABLE_ON_PAGE(th, th, th->len))
		return th;


	length = th->len;
	if (!TABLE_ON_PAGE(syst_pa, pa, sizeof(struct sfi_table_header)))
		sfi_unmap_memory(th, sizeof(struct sfi_table_header));

	return sfi_map_memory(pa, length);
}
