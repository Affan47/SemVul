all_lower (str)
     register char *str;
{
	while (*str) {
		if (!isascii ((Char) * str) || !islower ((Char) * str))
			return 0;
		++str;
	}

	return 1;
}
