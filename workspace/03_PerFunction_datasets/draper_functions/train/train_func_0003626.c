DelNavPoint(int nav)
{
	if (nav != -1)
	{
		if (nav != MAX_NAVPOINTS-1)
		{
			for (int i = nav; i < MAX_NAVPOINTS-1; i++)
			{
				Navs[nav] = Navs[nav+1];
			}

		}
		ZeroNav(MAX_NAVPOINTS-1);
		return true;
	}

	return false;
}
