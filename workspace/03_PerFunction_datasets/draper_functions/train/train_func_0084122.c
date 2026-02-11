symtab_insert_pos(struct grecs_symtab *st, void *elt)
{
	unsigned i;
	unsigned pos = st->hash_fun(elt, hash_size[st->hash_num]);

	for (i = pos; st->tab[i];) {
		if (++i >= hash_size[st->hash_num])
			i = 0;
		if (i == pos)

			abort();
	}
	return i;
}
