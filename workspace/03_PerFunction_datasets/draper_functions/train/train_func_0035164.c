check_locale(int category, const char *value)
{
	char	   *save;
	bool		ret;

	save = setlocale(category, NULL);
	if (!save)
		return false;


	save = pstrdup(save);


	ret = (setlocale(category, value) != NULL);

	setlocale(category, save);
	pfree(save);

	return ret;
}
