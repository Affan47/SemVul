VCC_FindSymbol(struct vcc *tl, const struct token *t, enum symkind kind)
{
	struct symbol *sym;

	assert(t->tok == ID);
	VTAILQ_FOREACH(sym, &tl->symbols, list) {
		if (sym->kind == SYM_WILDCARD &&
		   (t->e - t->b > sym->nlen) &&
		   !memcmp(sym->name, t->b, sym->nlen)) {
			AN (sym->wildcard);
			return (sym->wildcard(tl, t, sym));
		}
		if (kind != SYM_NONE && kind != sym->kind)
			continue;
		if (vcc_IdIs(t, sym->name))
			return (sym);
	}
	return (NULL);
}
