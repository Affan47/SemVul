pqGetCopyData3(PGconn *conn, char **buffer, int async)
{
	int			msgLength;

	for (;;)
	{


		msgLength = getCopyDataMessage(conn);
		if (msgLength < 0)
			return msgLength;
		if (msgLength == 0)
		{

			if (async)
				return 0;

			if (pqWait(TRUE, FALSE, conn) ||
				pqReadData(conn) < 0)
				return -2;
			continue;
		}


		msgLength -= 4;
		if (msgLength > 0)
		{
			*buffer = (char *) malloc(msgLength + 1);
			if (*buffer == NULL)
			{
				printfPQExpBuffer(&conn->errorMessage,
								  libpq_gettext("out of memory\n"));
				return -2;
			}
			memcpy(*buffer, &conn->inBuffer[conn->inCursor], msgLength);
			(*buffer)[msgLength] = '\0';


			conn->inStart = conn->inCursor + msgLength;

			return msgLength;
		}


		conn->inStart = conn->inCursor;
	}
}
