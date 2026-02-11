ProcessGuardOrder(Unit *u, AString *o, OrdersCheck *pCheck)
{

	AString *token = o->gettoken();
	if (!token) {
		ParseError(pCheck, u, 0, "GUARD: Invalid value.");
		return;
	}
	int val = ParseTF(token);
	delete token;
	if (val==-1) {
		ParseError(pCheck, u, 0, "GUARD: Invalid value.");
		return;
	}
	if(!pCheck) {
		if (val==0) {
			if (u->guard != GUARD_AVOID)
				u->guard = GUARD_NONE;
		} else {
			u->guard = GUARD_SET;
		}
	}
}
