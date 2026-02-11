notify(Widget	 gw,
		   XEvent	*event,
		   String	*params,
		   Cardinal	*no_params)
{
    ScrListWidget	w = (ScrListWidget)gw;
    XtCallbackList	c_list = w->scrlist.callback;
    long		i;

    if (!w->scrlist.active || !c_list)
	return;

    i = event_to_index(w, event);
    if (i < 0 || i >= LINES(w))
	return;

    XtCallCallbackList((Widget)w, c_list, (XtPointer)i);
}
