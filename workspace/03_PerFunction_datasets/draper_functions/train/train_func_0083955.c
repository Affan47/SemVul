read_strtab(FILE *in, const struct coff_header *hdr,
		       char **ret_tab)
{
	char *strtab;
	int file_size;
	int alloc_size;
	int strtab_len;
	int strtab_start = hdr->stab_count * STAB_ENTRY_SIZE + hdr->stab_start;

	if (fseek(in, 0, SEEK_END) < 0) {
		printc_err("coff: can't seek to end\n");
		return -1;
	}

	file_size = ftell(in);
	strtab_len = file_size - strtab_start;

	if (strtab_len < 0) {
		printc_err("coff: invalid string table size\n");
		return -1;
	}

	if (!strtab_len) {
		*ret_tab = NULL;
		return 0;
	}

	alloc_size = strtab_len + 1;
	strtab = malloc(alloc_size);
	if (!strtab) {
		pr_error("coff: can't allocate memory for string table");
		return -1;
	}

	if (read_block(in, strtab_start, strtab_len, strtab) < 0) {
		printc_err("coff: failed to read string table\n");
		free(strtab);
		return -1;
	}

	strtab[strtab_len] = 0;
	*ret_tab = strtab;
	return strtab_len;
}
