elf32_syms(FILE *in, stab_t stab)
{
	struct elf32_info info;
	Elf32_Shdr *s;
	int ret = 0;

	if (read_all(&info, in) < 0)
		return -1;

	s = find_shdr(&info, SHT_SYMTAB);
	if (!s) {
		printc_err("elf32: no symbol table\n");
		return -1;
	}

	if (s->sh_link <= 0 || s->sh_link >= info.file_ehdr.e_shnum) {
		printc_err("elf32: no string table\n");
		return -1;
	}

	if (syms_load_strings(&info, in, &info.file_shdrs[s->sh_link]) < 0 ||
	    syms_load_syms(&info, in, s, stab) < 0)
		ret = -1;

	if (info.string_tab)
		free(info.string_tab);

	return ret;
}
