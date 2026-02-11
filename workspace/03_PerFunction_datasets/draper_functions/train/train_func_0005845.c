read_integer(int *number)
{
	int nbr = 0;
	int nbr2;
	int c;
	bool minus = FALSE;

	c = get_char();

	if (c == '-')
	{
		minus = TRUE;
		c = get_char();
	}
	else if (c == '+')
		c = get_char();

	if ((c < 0) || !isdigit(c))
		return TRUE;

	for(;;)
	{
		nbr2 = nbr * 10 + (c - '0');
		if (nbr2 < nbr)
			return TRUE;
		nbr = nbr2;

		c = look_char();
		if ((c < 0) || !isdigit(c))
			break;

		buffer_pos++;
	}

	if (minus)
		nbr = (-nbr);

	*number = nbr;
	return FALSE;
}
