lookup_symbol_name(unsigned long addr, char *symname)
{
	symname[0] = '\0';
	symname[KSYM_NAME_LEN - 1] = '\0';

	if (is_ksym_addr(addr)) {
		unsigned long pos;

		pos = get_symbol_pos(addr, NULL, NULL);

		kallsyms_expand_symbol(get_symbol_offset(pos),
				       symname, KSYM_NAME_LEN);
		return 0;
	}

	return lookup_module_symbol_name(addr, symname);
}
