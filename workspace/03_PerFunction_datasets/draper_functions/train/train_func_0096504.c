wchar2char(char *to, const wchar_t *from, size_t tolen)
{
	size_t		result;

	if (tolen == 0)
		return 0;

#ifdef WIN32


	if (GetDatabaseEncoding() == PG_UTF8)
	{
		result = WideCharToMultiByte(CP_UTF8, 0, from, -1, to, tolen,
									 NULL, NULL);

		if (result <= 0)
			result = -1;
		else
		{
			Assert(result <= tolen);

			result--;
		}
	}
	else
#endif
	{
		Assert(!lc_ctype_is_c());
		result = wcstombs(to, from, tolen);
	}
	return result;
}
