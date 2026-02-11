FlocaleSetlocaleForX(
	int category, const char *locale, const char *module)
{
	if ((Flocale = setlocale(category, locale)) == NULL)
	{
		fprintf(stderr,
			"[%s][%s]: ERROR -- Cannot set locale. Please check"
			" your $LC_CTYPE or $LANG.\n",
			(module == NULL)? "" : module, "FlocaleSetlocaleForX");
		return;
	}
	if (!XSupportsLocale())
	{
		fprintf(stderr,
			"[%s][%s]: WARNING -- X does not support locale %s\n",
			(module == NULL)? "": module, "FlocaleSetlocaleForX",
			Flocale);
		Flocale = NULL;
	}
}
