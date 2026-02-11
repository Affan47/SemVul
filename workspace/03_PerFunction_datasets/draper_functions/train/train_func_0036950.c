preeditCaret(icp, caret)
IMIC *icp;
int caret;
{
    IMConnection *conn = icp->im->connection;
    int offset;

    if (icp->state & IC_RESETTING) return;

    preeditStart(icp);

    TRACE(("imlib:preeditCaret()\n"));

    offset = IMPutHeader(conn, XIM_PREEDIT_CARET, 0, 0);
    IMPutC16(conn, icp->im->id);
    IMPutC16(conn, icp->id);
    IMPutC32(conn, caret);
    IMPutC32(conn, (long)XIMAbsolutePosition);
    IMPutC32(conn, (long)XIMPrimary);
    IMFinishRequest(conn, offset);
}
