leftmostLoc(int loc1, int loc2)
{
	if (loc1 < 0)
		return loc2;
	else if (loc2 < 0)
		return loc1;
	else
		return Min(loc1, loc2);
}
