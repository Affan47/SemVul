RunQuitOrders()
{
	forlist(&factions) {
		Faction *f = (Faction *) elem;
		if (f->quit)
			Do1Quit(f);
	}
}
