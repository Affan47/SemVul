internal_cancel(SockAddr *raddr, int be_pid, int be_key,
				char *errbuf, int errbufsize)
{
	int			save_errno = SOCK_ERRNO;
	int			tmpsock = -1;
	char		sebuf[256];
	int			maxlen;
	struct
	{
		uint32		packetlen;
		CancelRequestPacket cp;
	}			crp;


	if ((tmpsock = socket(raddr->addr.ss_family, SOCK_STREAM, 0)) < 0)
	{
		strlcpy(errbuf, "PQcancel() -- socket() failed: ", errbufsize);
		goto cancel_errReturn;
	}
retry3:
	if (connect(tmpsock, (struct sockaddr *) & raddr->addr,
				raddr->salen) < 0)
	{
		if (SOCK_ERRNO == EINTR)

			goto retry3;
		strlcpy(errbuf, "PQcancel() -- connect() failed: ", errbufsize);
		goto cancel_errReturn;
	}


	crp.packetlen = htonl((uint32) sizeof(crp));
	crp.cp.cancelRequestCode = (MsgType) htonl(CANCEL_REQUEST_CODE);
	crp.cp.backendPID = htonl(be_pid);
	crp.cp.cancelAuthCode = htonl(be_key);

retry4:
	if (send(tmpsock, (char *) &crp, sizeof(crp), 0) != (int) sizeof(crp))
	{
		if (SOCK_ERRNO == EINTR)

			goto retry4;
		strlcpy(errbuf, "PQcancel() -- send() failed: ", errbufsize);
		goto cancel_errReturn;
	}


retry5:
	if (recv(tmpsock, (char *) &crp, 1, 0) < 0)
	{
		if (SOCK_ERRNO == EINTR)

			goto retry5;

	}


	closesocket(tmpsock);
	SOCK_ERRNO_SET(save_errno);
	return TRUE;

cancel_errReturn:


	maxlen = errbufsize - strlen(errbuf) - 2;
	if (maxlen >= 0)
	{
		strncat(errbuf, SOCK_STRERROR(SOCK_ERRNO, sebuf, sizeof(sebuf)),
				maxlen);
		strcat(errbuf, "\n");
	}
	if (tmpsock >= 0)
		closesocket(tmpsock);
	SOCK_ERRNO_SET(save_errno);
	return FALSE;
}
