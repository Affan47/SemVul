FtpAcceptConnection(netbuf *nData, netbuf *nControl)
{
    int sData;
    struct sockaddr addr;
    SOCKLEN_TYPE l;
    int i;
    struct timeval tv;
    fd_set mask;
    int rv;

    FD_ZERO(&mask);
    FD_SET(nControl->handle, &mask);
    FD_SET(nData->handle, &mask);
    tv.tv_usec = 0;
    tv.tv_sec = ACCEPT_TIMEOUT;
    i = nControl->handle;
    if (i < nData->handle)
	i = nData->handle;
    i = select(i+1, &mask, NULL, NULL, &tv);
    if (i == -1)
    {
        strncpy(nControl->response, strerror(errno),
                sizeof(nControl->response));
        net_close(nData->handle);
        nData->handle = 0;
        rv = 0;
    }
    else if (i == 0)
    {
	strcpy(nControl->response, "timed out waiting for connection");
	net_close(nData->handle);
	nData->handle = 0;
	rv = 0;
    }
    else
    {
	if (FD_ISSET(nData->handle, &mask))
	{
	    l = sizeof(addr);
	    sData = accept(nData->handle, &addr, &l);
	    i = errno;
	    net_close(nData->handle);
	    if (sData > 0)
	    {
		rv = 1;
		nData->handle = sData;
	    }
	    else
	    {
		strncpy(nControl->response, strerror(i),
                        sizeof(nControl->response));
		nData->handle = 0;
		rv = 0;
	    }
	}
	else if (FD_ISSET(nControl->handle, &mask))
	{
	    net_close(nData->handle);
	    nData->handle = 0;
	    readresp('2', nControl);
	    rv = 0;
	}
    }
    return rv;
}
