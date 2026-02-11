getNotify(PGconn *conn)
{
	int			be_pid;
	int			nmlen;
	PGnotify   *newNotify;

	if (pqGetInt(&be_pid, 4, conn))
		return EOF;
	if (pqGets(&conn->workBuffer, conn))
		return EOF;


	nmlen = strlen(conn->workBuffer.data);
	newNotify = (PGnotify *) malloc(sizeof(PGnotify) + nmlen + 1);
	if (newNotify)
	{
		newNotify->relname = (char *) newNotify + sizeof(PGnotify);
		strcpy(newNotify->relname, conn->workBuffer.data);

		newNotify->extra = newNotify->relname + nmlen;
		newNotify->be_pid = be_pid;
		newNotify->next = NULL;
		if (conn->notifyTail)
			conn->notifyTail->next = newNotify;
		else
			conn->notifyHead = newNotify;
		conn->notifyTail = newNotify;
	}

	return 0;
}
