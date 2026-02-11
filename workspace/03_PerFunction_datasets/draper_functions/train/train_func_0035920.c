hasWrongDayOrHour(Rules& r)
{
	if(maxBuildingChangesPerDay>r.nHoursPerDay)
		return true;

	return false;
}
