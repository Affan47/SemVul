getNotify(PGconn *conn)
{
	int			be_pid;
	char	   *svname;
	int			nmlen;
	int			extralen;
	PGnotify   *newNotify;

	if (pqGetInt(&be_pid, 4, conn))
		return EOF;
	if (pqGets(&conn->workBuffer, conn))
		return EOF;

	svname = strdup(conn->workBuffer.data);
	if (!svname)
		return EOF;
	if (pqGets(&conn->workBuffer, conn))
	{
		free(svname);
		return EOF;
	}


	nmlen = strlen(svname);
	extralen = strlen(conn->workBuffer.data);
	newNotify = (PGnotify *) malloc(sizeof(PGnotify) + nmlen + extralen + 2);
	if (newNotify)
	{
		newNotify->relname = (char *) newNotify + sizeof(PGnotify);
		strcpy(newNotify->relname, svname);
		newNotify->extra = newNotify->relname + nmlen + 1;
		strcpy(newNotify->extra, conn->workBuffer.data);
		newNotify->be_pid = be_pid;
		newNotify->next = NULL;
		if (conn->notifyTail)
			conn->notifyTail->next = newNotify;
		else
			conn->notifyHead = newNotify;
		conn->notifyTail = newNotify;
	}

	free(svname);
	return 0;
}
