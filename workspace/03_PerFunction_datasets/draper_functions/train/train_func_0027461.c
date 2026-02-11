WSASend (guint32 fd, WapiWSABuf *buffers, guint32 count, guint32 *sent,
	     guint32 flags, WapiOverlapped *overlapped,
	     WapiOverlappedCB *complete)
{
	int ret;
	struct msghdr hdr;

	g_assert (overlapped == NULL);
	g_assert (complete == NULL);

	wsabuf_to_msghdr (buffers, count, &hdr);
	ret = _wapi_sendmsg (fd, &hdr, flags);
	msghdr_iov_free (&hdr);

	if(ret == SOCKET_ERROR)
		return ret;

	*sent = ret;
	return 0;
}
