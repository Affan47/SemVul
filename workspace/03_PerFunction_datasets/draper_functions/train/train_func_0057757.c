vcc_ParseAction(struct vcc *tl)
{
	struct token *at;
	struct action_table *atp;
	const struct symbol *sym;

	at = tl->t;
	assert (at->tok == ID);
	for(atp = action_table; atp->name != NULL; atp++) {
		if (vcc_IdIs(at, atp->name)) {
			if (atp->bitmask != 0)
				vcc_AddUses(tl, at, atp->bitmask,
				    "not a valid action");
			atp->func(tl);
			return (1);
		}
	}
	sym = VCC_FindSymbol(tl, tl->t, SYM_NONE);
	if (sym != NULL && sym->kind == SYM_PROC) {
		vcc_Expr_Call(tl, sym);
		return (1);
	}
	return (0);
}
