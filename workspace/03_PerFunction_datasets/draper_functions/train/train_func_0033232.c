fixexttype(Namep var)
#endif
{
	Extsym *e;
	int type, type1;

	type = var->vtype;
	e = &extsymtab[var->vardesc.varno];
	if ((type1 = e->extype) && type == TYUNKNOWN)
		return var->vtype = type1;
	if (var->visused) {
		if (e->exused && type != type1)
			changedtype(var);
		e->exused = 1;
		e->extype = type;
		}
	return type;
	}
