module_locate_symbol(const char *modname, const char *sym)
{
	module_t *m;
	void *symptr;

	if (!(m = module_find_published(modname)))
	{
		slog(LG_ERROR, "module_locate_symbol(): %s is not loaded.", modname);
		return NULL;
	}

	if (modtarget != NULL && !mowgli_node_find(m, &modtarget->deplist))
	{
		slog(LG_DEBUG, "module_locate_symbol(): %s added as a dependency for %s (symbol: %s)",
			m->header->name, modtarget->header->name, sym);
		mowgli_node_add(m, mowgli_node_create(), &modtarget->deplist);
		mowgli_node_add(modtarget, mowgli_node_create(), &m->dephost);
	}

	symptr = linker_getsym(m->handle, sym);

	if (symptr == NULL)
		slog(LG_ERROR, "module_locate_symbol(): could not find symbol %s in module %s.", sym, modname);
	return symptr;
}
