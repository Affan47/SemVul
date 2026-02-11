_dxl_XRemoveWorkProc(DXLConnection *c)
{
    XEventHandlerData *xehd = (XEventHandlerData *)c->eventHandlerData;
    if (xehd && xehd->wpid != 0)
    {
	XtRemoveWorkProc(xehd->wpid);
	xehd->wpid = 0;
    }
}
