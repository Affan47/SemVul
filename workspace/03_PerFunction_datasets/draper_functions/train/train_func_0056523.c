ConnCreate(int serverFd)
{
	Port	   *port;

	if (!(port = (Port *) calloc(1, sizeof(Port))))
	{
		ereport(LOG,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("out of memory")));
		ExitPostmaster(1);
	}

	if (StreamConnection(serverFd, port) != STATUS_OK)
	{
		if (port->sock >= 0)
			StreamClose(port->sock);
		ConnFree(port);
		return NULL;
	}
	else
	{


		RandomSalt(port->cryptSalt, port->md5Salt);
	}


#ifndef EXEC_BACKEND
#if defined(ENABLE_GSS) || defined(ENABLE_SSPI)
	port->gss = (pg_gssinfo *) calloc(1, sizeof(pg_gssinfo));
	if (!port->gss)
	{
		ereport(LOG,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("out of memory")));
		ExitPostmaster(1);
	}
#endif
#endif

	return port;
}
