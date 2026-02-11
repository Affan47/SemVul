CAlistopen(FromServer, ToServer, request)
    FILE	*FromServer;
    FILE	*ToServer;
    char	*request;
{

    if (FromServer == NULL || ToServer == NULL)
	return NULL;

    (void)strcpy(CApathname, _PATH_TEMPACTIVE);
    (void)mktemp(CApathname);
    return CAfp = CA_listopen(CApathname, FromServer, ToServer, request);
}
