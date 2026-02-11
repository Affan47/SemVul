ProcessAdvanceOrder(Unit *u, AString *o, OrdersCheck *pCheck)
{
	MoveOrder *m = 0;

	if ((u->monthorders && u->monthorders->type != O_ADVANCE) ||
		(Globals->TAX_PILLAGE_MONTH_LONG &&
		 ((u->taxing == TAX_TAX) || (u->taxing == TAX_PILLAGE)))) {
		AString err = "ADVANCE: Overwriting previous ";
		if (u->inTurnBlock) err += "DELAYED ";
		err += "month-long orders";
		ParseError(pCheck, u, 0, err);
		if (u->monthorders) delete u->monthorders;
		u->monthorders = 0;
	}
	if(Globals->TAX_PILLAGE_MONTH_LONG) u->taxing = TAX_NONE;
	if (!u->monthorders) {
		u->monthorders = new MoveOrder;
		u->monthorders->type = O_ADVANCE;
	}
	m = (MoveOrder *) u->monthorders;
	m->advancing = 1;

	for (;;) {
		AString *t = o->gettoken();
		if (!t) return;
		int d = ParseDir(t);
		delete t;
		if (d!=-1) {
			if(!pCheck) {
				MoveDir *x = new MoveDir;
				x->dir = d;
				m->dirs.Add(x);
			}
		} else {
			ParseError(pCheck, u, 0, "ADVANCE: Warning, bad direction.");
			return;
		}
	}
}
