IMPutString(conn, s, len)
IMConnection *conn;
char *s;
int len;
{
    if (len < 0) len = strlen(s);
    IMBufAdd(&conn->out_buf, s, len);
}
