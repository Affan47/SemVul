getFullHouse() const
{
	int i;
	bool three, two;
	three = false;
	i = 0;
	while (!three && i <= 6)
	{
		if (getSimilar(i) == 3) three = true;
		else i++;
	}
	if (three)
	{
		two = false;
		i = 0;
		while (!two && i <= 6)
		{
			if (getSimilar(i) == 2) two = true;
			else i++;
		}
		if (two) return 25;
	}
	return 0;
}
