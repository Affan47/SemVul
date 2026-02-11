parse_crash_elf_headers(void)
{
	unsigned char e_ident[EI_NIDENT];
	u64 addr;
	int rc=0;

	addr = elfcorehdr_addr;
	rc = elfcorehdr_read(e_ident, EI_NIDENT, &addr);
	if (rc < 0)
		return rc;
	if (memcmp(e_ident, ELFMAG, SELFMAG) != 0) {
		pr_warn("Warning: Core image elf header not found\n");
		return -EINVAL;
	}

	if (e_ident[EI_CLASS] == ELFCLASS64) {
		rc = parse_crash_elf64_headers();
		if (rc)
			return rc;
	} else if (e_ident[EI_CLASS] == ELFCLASS32) {
		rc = parse_crash_elf32_headers();
		if (rc)
			return rc;
	} else {
		pr_warn("Warning: Core image elf header is not sane\n");
		return -EINVAL;
	}


	vmcore_size = get_vmcore_size(elfcorebuf_sz, elfnotes_sz,
				      &vmcore_list);

	return 0;
}
