event_to_wire (Display *dpy, XEvent *re, xEvent *event)
{
    XExtDisplayInfo *info = find_display (dpy);
    XShapeEvent		*se;
    xShapeNotifyEvent	*sevent;

    ShapeCheckExtension (dpy, info, 0);

    switch ((re->type & 0x7f) - info->codes->first_event) {
    case ShapeNotify:
    	se = (XShapeEvent *) re;
	sevent = (xShapeNotifyEvent *) event;
    	sevent->type = se->type | (se->send_event ? 0x80 : 0);
    	sevent->sequenceNumber = se->serial & 0xffff;
    	sevent->window = se->window;
    	sevent->kind = se->kind;
    	sevent->x = se->x;
    	sevent->y = se->y;
    	sevent->width = se->width;
    	sevent->height = se->height;
	sevent->time = se->time;
    	return 1;
    }
    return 0;
}
