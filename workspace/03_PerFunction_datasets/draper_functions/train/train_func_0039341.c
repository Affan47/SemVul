rproc_elf_find_rsc_table(struct rproc *rproc, const struct firmware *fw,
			 int *tablesz)
{
	struct elf32_hdr *ehdr;
	struct elf32_shdr *shdr;
	struct device *dev = &rproc->dev;
	struct resource_table *table = NULL;
	const u8 *elf_data = fw->data;

	ehdr = (struct elf32_hdr *)elf_data;

	shdr = find_table(dev, ehdr, fw->size);
	if (!shdr)
		return NULL;

	table = (struct resource_table *)(elf_data + shdr->sh_offset);
	*tablesz = shdr->sh_size;

	return table;
}
