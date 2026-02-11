grab_one_flag(u32b *flags, cptr names[], cptr what)
{
	int i;


	for (i = 0; i < 32 && names[i]; i++)
	{
		if (streq(what, names[i]))
		{
			*flags |= (1L << i);
			return (0);
		}
	}

	return (-1);
}
