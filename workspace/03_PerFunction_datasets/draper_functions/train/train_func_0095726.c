find_symbol_in_section(const struct symsearch *syms,
				   struct module *owner,
				   void *data)
{
	struct find_symbol_arg *fsa = data;
	struct kernel_symbol *sym;

	sym = bsearch(fsa->name, syms->start, syms->stop - syms->start,
			sizeof(struct kernel_symbol), cmp_name);

	if (sym != NULL && check_symbol(syms, owner, sym - syms->start, data))
		return true;

	return false;
}
