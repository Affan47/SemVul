ProcessFindOrder(Unit *u, AString *o, OrdersCheck *pCheck)
{
	AString *token = o->gettoken();
	if (!token) {
		ParseError(pCheck, u, 0, "FIND: No faction number given.");
		return;
	}
	int n = token->value();
	int is_all = (*token == "all");
	delete token;
	if (n==0 && !is_all) {
		ParseError(pCheck, u, 0, "FIND: No faction number given.");
		return;
	}
	if(!pCheck) {
		FindOrder *f = new FindOrder;
		f->find = n;
		u->findorders.Add(f);
	}
}
