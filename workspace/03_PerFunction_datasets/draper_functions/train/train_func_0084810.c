IMPutHeader(conn, major, minor, arglen)
IMConnection *conn;
int major;
int minor;
int arglen;
{
    int offset;

    offset = IMBUFLEN(&conn->out_buf);
    arglen = (arglen + 3) / 4;
#ifdef XIM_BC
    if (conn->has_length_bug) arglen *= 4;
#endif
    IMPutC8(conn, major);
    IMPutC8(conn, minor);
    IMPutC16(conn, (unsigned int)arglen);
    return offset;
}
