VCC_WalkSymbols(struct vcc *tl, symwalk_f *func, enum symkind kind)
{
	struct symbol *sym;

	VTAILQ_FOREACH(sym, &tl->symbols, list) {
		if (kind == SYM_NONE || kind == sym->kind)
			func(tl, sym);
		ERRCHK(tl);
	}
}
