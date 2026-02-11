pqGetline2(PGconn *conn, char *s, int maxlen)
{
	int			result = 1;

	if (conn->sock == PGINVALID_SOCKET ||
		conn->asyncStatus != PGASYNC_COPY_OUT)
	{
		*s = '\0';
		return EOF;
	}


	while (maxlen > 1)
	{
		if (conn->inStart < conn->inEnd)
		{
			char		c = conn->inBuffer[conn->inStart++];

			if (c == '\n')
			{
				result = 0;
				break;
			}
			*s++ = c;
			maxlen--;
		}
		else
		{

			if (pqWait(TRUE, FALSE, conn) ||
				pqReadData(conn) < 0)
			{
				result = EOF;
				break;
			}
		}
	}
	*s = '\0';

	return result;
}
