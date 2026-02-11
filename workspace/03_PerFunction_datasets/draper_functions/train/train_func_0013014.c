find_table(struct device *dev, struct elf32_hdr *ehdr, size_t fw_size)
{
	struct elf32_shdr *shdr;
	int i;
	const char *name_table;
	struct resource_table *table = NULL;
	const u8 *elf_data = (void *)ehdr;


	shdr = (struct elf32_shdr *)(elf_data + ehdr->e_shoff);
	name_table = elf_data + shdr[ehdr->e_shstrndx].sh_offset;

	for (i = 0; i < ehdr->e_shnum; i++, shdr++) {
		u32 size = shdr->sh_size;
		u32 offset = shdr->sh_offset;

		if (strcmp(name_table + shdr->sh_name, ".resource_table"))
			continue;

		table = (struct resource_table *)(elf_data + offset);


		if (offset + size > fw_size || offset + size < size) {
			dev_err(dev, "resource table truncated\n");
			return NULL;
		}


		if (sizeof(struct resource_table) > size) {
			dev_err(dev, "header-less resource table\n");
			return NULL;
		}


		if (table->ver != 1) {
			dev_err(dev, "unsupported fw ver: %d\n", table->ver);
			return NULL;
		}


		if (table->reserved[0] || table->reserved[1]) {
			dev_err(dev, "non zero reserved bytes\n");
			return NULL;
		}


		if (table->num * sizeof(table->offset[0]) +
				sizeof(struct resource_table) > size) {
			dev_err(dev, "resource table incomplete\n");
			return NULL;
		}

		return shdr;
	}

	return NULL;
}
