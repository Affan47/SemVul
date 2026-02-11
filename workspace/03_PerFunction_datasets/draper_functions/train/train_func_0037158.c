FlocaleInit(
	int category, const char *locale, const char *modifiers,
	const char *module)
{

	FlocaleSetlocaleForX(category, locale, module);
	if (Flocale == NULL)
		return;

	if (modifiers != NULL &&
	    (Fmodifiers = XSetLocaleModifiers(modifiers)) == NULL)
	{
		fprintf(stderr,
			"[%s][%s]: WARNING -- Cannot set locale modifiers\n",
			(module == NULL)? "": module, "FlocaleInit");
	}
#if FLOCALE_DEBUG_SETLOCALE
	fprintf(stderr,"[%s][FlocaleInit] locale: %s, modifier: %s\n",
		module, Flocale, Fmodifiers);
#endif
}
