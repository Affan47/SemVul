DeleteDeadFactions()
{
	forlist(&factions) {
		Faction *fac = (Faction *) elem;
		if (!fac->IsNPC() && !fac->exists) {
			factions.Remove(fac);
			forlist((&factions))
				((Faction *) elem)->RemoveAttitude(fac->num);
			delete fac;
		}
	}
}
