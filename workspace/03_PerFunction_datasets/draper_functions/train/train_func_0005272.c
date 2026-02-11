GetAttitude(ARegion *r, Unit *u)
{
	if (faction == u->faction) return A_ALLY;
	int att = faction->GetAttitude(u->faction->num);
	if (att >= A_FRIENDLY && att >= faction->defaultattitude) return att;

	if (CanSee(r, u) == 2)
		return att;
	else
		return faction->defaultattitude;
}
