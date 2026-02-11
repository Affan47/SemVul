CAopen(FromServer, ToServer)
    FILE	*FromServer;
    FILE	*ToServer;
{


    if ((CAfp = fopen(_PATH_CLIENTACTIVE, "r")) != NULL) {
	CApathname[0] = '\0';
	return CAfp;
    }


    return CAlistopen(FromServer, ToServer, (char *)NULL);
}
