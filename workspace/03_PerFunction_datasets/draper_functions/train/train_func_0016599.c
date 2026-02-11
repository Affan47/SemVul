damcalc(int num, int sides, aspect dam_aspect)
{
	int val = 0;

	switch (dam_aspect)
	{
		case MAXIMISE:
		case EXTREMIFY:
		{
			val = num * sides;
			break;
		}
		case RANDOMISE:
		{
			val = damroll(num, sides);
			break;
		}
		case MINIMISE:
		{
			val = num;
			break;
		}
		case AVERAGE:
		{
			val = num * (sides + 1) / 2;
			break;
		}
	}

	return (val);
}
