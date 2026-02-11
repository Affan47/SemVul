mangleunit (int unit)
{
	if (unit <= 99)
		return unit;
	if (unit == 100)
		return 8;
	if (unit == 110)
		return 9;
	return -1;
}
