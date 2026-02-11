login_to_database(BCPPARAMDATA * pdata, DBPROCESS ** pdbproc)
{
	LOGINREC *login;


	if (dbinit() == FAIL)
		return (FALSE);


	dberrhandle(err_handler);
	dbmsghandle(msg_handler);


	if (pdata->interfacesfile != NULL)
		dbsetifile(pdata->interfacesfile);


	login = dblogin();
	if (!login)
		return FALSE;

	if (pdata->user)
		DBSETLUSER(login, pdata->user);
	if (pdata->pass) {
		DBSETLPWD(login, pdata->pass);
		memset(pdata->pass, 0, strlen(pdata->pass));
	}

	DBSETLAPP(login, "FreeBCP");
	if (pdata->charset)
		DBSETLCHARSET(login, pdata->charset);

	if (pdata->Aflag && pdata->packetsize > 0) {
		DBSETLPACKET(login, pdata->packetsize);
	}


	BCP_SETL(login, TRUE);


	if ((*pdbproc = dbopen(login, pdata->server)) == NULL) {
		fprintf(stderr, "Can't connect to server \"%s\".\n", pdata->server);
		dbloginfree(login);
		return (FALSE);
	}
	dbloginfree(login);
	login = NULL;


	if (pdata->hint) {
		int erc = bcp_options(*pdbproc, BCPHINTS, (BYTE *) pdata->hint, strlen(pdata->hint));

		if (erc != SUCCEED)
			fprintf(stderr, "db-lib: Unable to set hint \"%s\"\n", pdata->hint);
		return FALSE;
	}

	return (TRUE);

}
