pqGetnchar(char *s, size_t len, PGconn *conn)
{
	if (len < 0 || len > (size_t) (conn->inEnd - conn->inCursor))
		return EOF;

	memcpy(s, conn->inBuffer + conn->inCursor, len);


	conn->inCursor += len;

	if (conn->Pfdebug)
	{
		fprintf(conn->Pfdebug, "From backend (%lu)> ", (unsigned long) len);
		fputnbytes(conn->Pfdebug, s, len);
		fprintf(conn->Pfdebug, "\n");
	}

	return 0;
}
