ProcessDistributeOrder(Unit *u, AString *o, OrdersCheck *pCheck)
{
	UnitId *tar = ParseUnit(o);
	if (!tar) {
		ParseError(pCheck, u, 0, "DISTRIBUTE: Invalid target.");
		return;
	}
	AString *token = o->gettoken();
	if (!token) {
		ParseError(pCheck, u, 0, "DISTRIBUTE: No amount given.");
		return;
	}

	int amt;
	if (*token == "all")
		amt = -1;
	else
		amt = token->value();
	delete token;
	token = o->gettoken();
	if (!token) {
		ParseError(pCheck, u, 0, "DISTRIBUTE: No item given.");
		return;
	}
	int item = ParseTransportableItem(token);
	delete token;
	if (item == -1) {
		ParseError(pCheck, u, 0, "DISTRIBUTE: Invalid item.");
		return;
	}

	int except = 0;
	token = o->gettoken();
	if (token && *token == "except") {
		delete token;
		token = o->gettoken();
		if (!token) {
			ParseError(pCheck, u, 0, "DISTRIBUTE: EXCEPT requires a value.");
			return;
		}
		except = token->value();
		delete token;
		if (except <= 0) {
			ParseError(pCheck, u, 0, "DISTRIBUTE: Invalid except value.");
			return;
		}
	}

	if (!pCheck) {
		TransportOrder *order = new TransportOrder;
		order->type = O_DISTRIBUTE;
		order->item = item;
		order->target = tar;
		order->amount = amt;
		order->except = except;
		u->transportorders.Add(order);
	}
	return;
}
