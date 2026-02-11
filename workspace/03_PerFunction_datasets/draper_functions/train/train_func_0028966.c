DetermineTownSize()
{

	if(getrandom(300) < Globals->TOWN_DEVELOPMENT) {
		return TOWN_CITY;
	}

	if(getrandom(220) < Globals->TOWN_DEVELOPMENT + 10) {
		return TOWN_TOWN;
	}

	return TOWN_VILLAGE;
}
