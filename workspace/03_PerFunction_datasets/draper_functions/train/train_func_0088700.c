_tabCallback(const char *szTabStops,
									const char *szDflTabStop)
{

	if (szTabStops)
		addOrReplaceVecProp("tabstops", g_strdup(szTabStops));
	if (szDflTabStop)
		addOrReplaceVecProp("default-tab-interval", g_strdup(szDflTabStop));
}
