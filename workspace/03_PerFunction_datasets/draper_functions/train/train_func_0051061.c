porges_strlen2(char *s)
{
	int i = 0;
	int iBefore = 0;
	int count = 0;

	while (s[i] > 0)
ascii:  i++;

	count += i-iBefore;
	while (s[i])
	{
		if (s[i] > 0)
		{
			iBefore = i;
			goto ascii;
		}
		else
			switch (0xF0 & s[i])
		{
			case 0xE0: i += 3; break;
			case 0xF0: i += 4; break;
			default:   i += 2; break;
		}
		++count;
	}
	return count;
}
