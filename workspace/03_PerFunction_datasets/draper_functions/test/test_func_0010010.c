c_encode(char uc)
{
	if (uc < 26)
	{
		return 'A'+uc;
	}
	if (uc < 52)
	{
		return 'a'+(uc-26);
	}
    if (uc < 62)
	{
		return '0'+(uc-52);
	}
	if (uc == 62)
	{
		return '+';
	}
	return '/';
}
