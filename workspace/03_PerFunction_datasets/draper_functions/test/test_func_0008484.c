get_efi_runtime_map(struct efi_mem_descriptor **map)
{
	DIR *dirp;
	struct dirent *entry;
	char filename[1024];
	struct efi_mem_descriptor md, *p = NULL;
	int nr_maps = 0;

	dirp = opendir("/sys/firmware/efi/runtime-map");
	if (!dirp)
		return 0;
	while ((entry = readdir(dirp)) != NULL) {
		sprintf(filename,
			"/sys/firmware/efi/runtime-map/%s",
			(char *)entry->d_name);
		if (*entry->d_name == '.')
			continue;
		file_scanf(filename, "type", "0x%x", (unsigned int *)&md.type);
		file_scanf(filename, "phys_addr", "0x%llx",
			   (unsigned long long *)&md.phys_addr);
		file_scanf(filename, "virt_addr", "0x%llx",
			   (unsigned long long *)&md.virt_addr);
		file_scanf(filename, "num_pages", "0x%llx",
			   (unsigned long long *)&md.num_pages);
		file_scanf(filename, "attribute", "0x%llx",
			   (unsigned long long *)&md.attribute);
		p = realloc(p, (nr_maps + 1) * sizeof(md));
		if (!p)
			goto err_out;

		*(p + nr_maps) = md;
		*map = p;
		nr_maps++;
	}

	closedir(dirp);
	return nr_maps;
err_out:
	if (map)
		free(map);
	closedir(dirp);
	return 0;
}
