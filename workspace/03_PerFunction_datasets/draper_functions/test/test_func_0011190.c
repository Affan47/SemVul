macro_find_maybe(cptr pat)
{
	int i;


	if (!macro__use[(byte)(pat[0])])
		return -1;


	for (i = 0; i < macro__num; ++i)
	{
		if (prefix(macro__pat[i], pat) && !streq(macro__pat[i], pat))
			return i;
	}


	return -1;
}
