saveEvent(ImageWindow *iw, int event, int state)
{
    Array b = iw->events;
    int n;
    DXEvent ev;

    if (!b)
    {
	iw->events = DXNewArray(TYPE_INT, CATEGORY_REAL, 1, sizeof(DXEvent)/DXTypeSize(TYPE_INT));
	b = iw->events;
    }

    switch (event)
    {
	case DXEVENT_LEFT:
	case DXEVENT_MIDDLE:
	case DXEVENT_RIGHT:
	{
	    DXMouseEvent *mev = (DXMouseEvent *)&ev;
	    mev->event      = event;
	    mev->x          = iw->x;
	    mev->y          = iw->y;
	    mev->kstate     = iw->kstate;
	    mev->state      = state;
	    break;
	}

	case DXEVENT_KEYPRESS:
	{
	    DXKeyPressEvent *kpev = (DXKeyPressEvent *)&ev;
	    kpev->event = event;
	    kpev->x     = iw->x;
	    kpev->y     = iw->y;
	    kpev->key   = state;
	    kpev->kstate = iw->kstate;
	    break;
	}
    }

    DXGetArrayInfo(b, &n, NULL, NULL, NULL, NULL);
    if (! DXAddArrayData(b, n, 1, (Pointer)&ev))
	goto error;


    return OK;

error:
    return ERROR;
}
