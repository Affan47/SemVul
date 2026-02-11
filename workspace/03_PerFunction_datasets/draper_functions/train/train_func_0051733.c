deleteSymbol(Address *Addr)
{
	Location *a = getLocationByAddress(Addr);
	if (a) {
		disableSymbol(a->label);
		a->label = NULL;
		symbol_count--;
	}
}
