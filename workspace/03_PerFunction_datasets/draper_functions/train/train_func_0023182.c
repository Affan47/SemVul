cgiGetCookie (s_cgi *parms, const char *name)
{
    int i;

    if (!parms || !parms->cookies)
	return NULL;
    for (i=0;parms->cookies[i]; i++)
	if (parms->cookies[i]->name && parms->cookies[i]->value && !strcmp(name,parms->cookies[i]->name)) {
	    cgiDebugOutput (1, "%s found as %s\n", name, parms->cookies[i]->value);
	    return parms->cookies[i];
	}
    cgiDebugOutput (1, "%s not found\n", name);
    return NULL;
}
