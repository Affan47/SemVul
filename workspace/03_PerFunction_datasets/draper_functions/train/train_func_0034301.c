hint_input(void)
{
	type8 c1, c2, c3;

	output_text(">>");
	ms_flush();

	do
	{
		c1 = ms_getchar(0);
	}
	while (c1 == '\n');
	if (c1 == 1)
		return -1;

	c2 = ms_getchar(0);
	if (c2 == 1)
		return -1;


	c3 = c2;
	while (c3 != '\n')
	{
		c3 = ms_getchar(0);
		if (c3 == 1)
			return -1;
	}
	ms_putchar('\n');

	if ((c1 >= '0') && (c1 <= '9'))
	{
		type16 number = c1 - '0';
		if ((c2 >= '0') && (c2 <= '9'))
		{
			number *= 10;
			number += c2 - '0';
		}
		return number;
	}

	if ((c1 >= 'A') && (c1 <= 'Z'))
		c1 = 'a' + (c1 - 'A');
	if ((c1 >= 'a') && (c1 <= 'z'))
	{
		switch (c1)
		{
		case 'e':
			return -2;
		case 'n':
			return -3;
		case 'p':
			return -4;
		}
	}
	return 0;
}
