ProcessTaxOrder(Unit *u, OrdersCheck *pCheck)
{
	if (u->taxing == TAX_PILLAGE) {
		ParseError(pCheck, u, 0, "TAX: The unit is already pillaging.");
		return;
	}
	if(Globals->TAX_PILLAGE_MONTH_LONG && u->monthorders) {
		delete u->monthorders;
		u->monthorders = NULL;
		AString err = "TAX: Overwriting previous ";
		if (u->inTurnBlock) err += "DELAYED ";
		err += "month-long order.";
		ParseError(pCheck, u, 0, err);
	}

	u->taxing = TAX_TAX;
}
