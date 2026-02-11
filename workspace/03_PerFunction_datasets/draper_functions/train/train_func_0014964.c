GetDeskNumber(char *action, int current_desk)
{
	int n;
	int m;
	int is_relative;
	int desk;
	int val[4];
	int min, max;

	if (MatchToken(action, "prev"))
	{
		return prev_desk;
	}
	n = GetIntegerArguments(action, NULL, &(val[0]), 4);
	if (n <= 0)
	{
		return Scr.CurrentDesk;
	}
	if (n == 1)
	{
		return current_desk + val[0];
	}
	desk = current_desk;
	m = 0;
	if (val[0] == 0)
	{

		desk = val[1];
		is_relative = 0;
	}
	else
	{

		desk += val[0];
		is_relative = 1;
	}
	if (n == 3)
	{
		m = 1;
	}
	if (n == 4)
	{
		m = 2;
	}
	if (n > 2)
	{

		if (val[m] <= val[m+1])
		{
			min = val[m];
			max = val[m+1];
		}
		else
		{

			min = val[m+1];
			max = val[m];
		}
		if (is_relative)
		{

			if (desk < min)
			{
				desk += (max - min + 1);
			}
			else if (desk > max)
			{
				desk -= (max - min + 1);
			}
		}
		else if (desk < min)
		{

			if (val[0] < 0)
			{
				desk = max;
			}
			else
			{
				desk = min;
			}
		}
		else if (desk > max)
		{

			if (val[0] > 0)
			{
				desk = min;
			}
			else
			{
				desk = max;
			}
		}
	}

	return desk;
}
