FcInitLoadOwnConfig (FcConfig *config)
{
    if (!config)
    {
	config = FcConfigCreate ();
	if (!config)
	    return NULL;
    }

    FcInitDebug ();

    if (!FcConfigParseAndLoad (config, 0, FcTrue))
    {
	const FcChar8 *sysroot = FcConfigGetSysRoot (config);
	FcConfig *fallback = FcInitFallbackConfig (sysroot);

	FcConfigDestroy (config);

	return fallback;
    }

    if (config->cacheDirs && config->cacheDirs->num == 0)
    {
	FcChar8 *prefix, *p;
	size_t plen;

	fprintf (stderr,
		 "Fontconfig warning: no <cachedir> elements found. Check configuration.\n");
	fprintf (stderr,
		 "Fontconfig warning: adding <cachedir>%s</cachedir>\n",
		 FC_CACHEDIR);
	prefix = FcConfigXdgCacheHome ();
	if (!prefix)
	    goto bail;
	plen = strlen ((const char *)prefix);
	p = realloc (prefix, plen + 12);
	if (!p)
	    goto bail;
	prefix = p;
	memcpy (&prefix[plen], FC_DIR_SEPARATOR_S "fontconfig", 11);
	prefix[plen + 11] = 0;
	fprintf (stderr,
		 "Fontconfig warning: adding <cachedir prefix=\"xdg\">fontconfig</cachedir>\n");

	if (!FcConfigAddCacheDir (config, (FcChar8 *) FC_CACHEDIR) ||
	    !FcConfigAddCacheDir (config, (FcChar8 *) prefix))
	{
	    FcConfig *fallback;
	    const FcChar8 *sysroot;

	  bail:
	    sysroot = FcConfigGetSysRoot (config);
	    fprintf (stderr,
		     "Fontconfig error: out of memory");
	    if (prefix)
		FcStrFree (prefix);
	    fallback = FcInitFallbackConfig (sysroot);
	    FcConfigDestroy (config);

	    return fallback;
	}
	FcStrFree (prefix);
    }

    return config;
}
