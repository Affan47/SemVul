IMGetICValues(icp, data, len, offset)
IMIC *icp;
char *data;
int len;
int offset;
{
    int nested_separator;
    int r;
    IMConnection *conn = icp->im->connection;
    int pos, list_start, list_end;

    TRACE(("IMGetICValues()\n"));

    pos = IMWritePos(conn);
    IMPutC16(conn, 0);
    IMPutC16(conn, 0);

    list_start = IMWritePos(conn);

    r = getICValues(icp, data, len, NEST_NONE, offset, &nested_separator);
    if (r < 0) return -1;

    list_end = IMWritePos(conn);
    IMRewriteC16(conn, pos, (unsigned int)(list_end - list_start));

    if (nested_separator) {


	DPRINT(("getICvalues: unmatched separator\n"));
	IMCancelRequest(icp->im->connection, offset);
	IMSendError(icp->im->connection, IMBadSomething, icp->im->id, icp->id,
		    "corrupted nested list");
	return -1;
    }
    return 0;
}
