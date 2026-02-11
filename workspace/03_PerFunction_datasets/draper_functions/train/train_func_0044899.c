pqDropConnection(PGconn *conn)
{

	pqsecure_close(conn);

	if (conn->sock != PGINVALID_SOCKET)
		closesocket(conn->sock);
	conn->sock = PGINVALID_SOCKET;

	conn->inStart = conn->inCursor = conn->inEnd = 0;
	conn->outCount = 0;
}
