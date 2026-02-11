symtab_register_data(
	struct symbol_table *symtab,
	struct slist *seg,
	unsigned int nesting_level,
	enum segment_kind loc
)
{
	struct slist_entry *i;
	struct data_definition *d;

	for (i = seg->first; i != NULL; i = i->next) {
		d = (struct data_definition *)i->data;

		d->nesting_level = nesting_level;
		d->loc = loc;
		symtab_register_data_ref(symtab, d, nesting_level);

		symbol_resolve_type_element(symtab, d->type, 0);
		symtab_resolver_resolve(symtab,	d);
	}
}
