free_service(aClient *cptr)
{
	aService	*serv;

	if ((serv = cptr->service))
	{
		if (serv->nexts)
			serv->nexts->prevs = serv->prevs;
		if (serv->prevs)
			serv->prevs->nexts = serv->nexts;
		if (svctop == serv)
			svctop = serv->nexts;


		if (serv->server)
			MyFree(serv->server);
		MyFree(serv);
		cptr->service = NULL;
	}
}
