ProcessPasswordOrder(Unit *u, AString *o, OrdersCheck *pCheck)
{
	if(pCheck) return;

	AString *token = o->gettoken();
	if (u->faction->password) delete u->faction->password;
	if (token) {
		u->faction->password = token;
		u->faction->Event(AString("Password is now: ") + *token);
	} else {
		u->faction->password = new AString("none");
		u->faction->Event("Password cleared.");
	}
}
