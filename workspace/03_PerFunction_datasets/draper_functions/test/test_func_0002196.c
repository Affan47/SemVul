postprint(unsigned int badness)
{
	if (coloron)
	{
		coloron = 0;
		printf(COLRESET);
	}

	if (usemarkers)
	{
		if (badness >= 100)
		{
			printf(" *");
		}
		else
		{
			if (almostcrit && badness >= almostcrit)
				printf(" +");
		}
	}

	printf("\n");
}
