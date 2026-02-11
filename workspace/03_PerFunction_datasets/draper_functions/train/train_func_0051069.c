SetValues (gcurrent, grequest, gnew, args, num_args)
    Widget gcurrent, grequest, gnew;
    ArgList args;
    Cardinal *num_args;
{
    NetstatWidget current = (NetstatWidget) gcurrent;
    NetstatWidget new = (NetstatWidget) gnew;
    Boolean redisplay = FALSE;

    if (current->netstat.update != new->netstat.update) {
	if (current->netstat.interval_id)
	  XtRemoveTimeOut (current->netstat.interval_id);
	new->netstat.interval_id =
	    XtAppAddTimeOut (XtWidgetToApplicationContext(gnew),
			     new->netstat.update * 100, clock_tic,
			     (XtPointer) gnew);
    }

    if (current->netstat.foreground_pixel != new->netstat.foreground_pixel ||
	current->core.background_pixel != new->core.background_pixel) {
	XtReleaseGC (gcurrent, current->netstat.gc);
	new->netstat.gc = get_netstat_gc (new);
	redisplay = TRUE;
    }

    return (redisplay);
}
