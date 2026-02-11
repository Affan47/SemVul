is_reloc(enum symtype type, const char *sym_name)
{
	return sym_regex[type] &&
		!regexec(&sym_regex_c[type], sym_name, 0, NULL, 0);
}
