GetUnitId(UnitId *id, int faction, ARegion *cur)
{
	Location *retval = NULL;

	retval = cur->GetLocation(id, faction);
	if (retval) return retval;


	if (!id->unitnum) return NULL;

	return this->FindUnit(id->unitnum);
}
