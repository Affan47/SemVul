getFocusWindow(icp, id, nest, offset, data, len)
IMIC *icp;
unsigned int id;
int nest;
int offset;
char *data;
int len;
{
    IMConnection *conn = icp->im->connection;

    TRACE(("imlib:getFocusWindow()\n"));

    if (!(icp->common_attr.set_mask & ATTR_MASK_FOCUS)) {

	fillCommonDefault(icp, (unsigned long)ATTR_MASK_FOCUS);
    }

    if (icp->common_attr.set_mask & ATTR_MASK_FOCUS) {
	IMPutC16(conn, id);
	IMPutC16(conn, 4);
	IMPutC32(conn, icp->common_attr.focus);
	return 0;
    } else {


	DPRINT(("getFocusWindow without setting focus/client window previously\n"));
	IMCancelRequest(conn, offset);
	IMSendError(conn, IMBadFocusWindow, icp->im->id, icp->id,
		    "neither of client/focus window not specified yet");
	return -1;
    }
}
