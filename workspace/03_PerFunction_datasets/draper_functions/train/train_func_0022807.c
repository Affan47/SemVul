EventToInputObject(w, event, args, num_args)
Widget w;
XEvent *event;
String *args;
Cardinal *num_args;
{
    ConversionControlWidget ccw = (ConversionControlWidget)w;
    Boolean hascallback = False;
    int r;
#ifdef OBSOLETE_FEATURE
    Boolean sendback = False;
#endif

    if (ccw->ccontrol.inputobj == NULL) return;

    ccw->ccontrol.endnotify = False;

    if (ccw->ccontrol.unusedeventcallback != NULL &&
	XtHasCallbacks(w, XtNunusedEventCallback) == XtCallbackHasSome) {
	hascallback = True;
    }

#ifdef OBSOLETE_FEATURE


    if ((hascallback ||ccw->ccontrol.sendbackKeyPress) &&
	event->type == KeyPress &&
	ICNumSegments(ccw->ccontrol.inputobj) == 0) {
	sendback = True;
    }

    ccw->ccontrol.eventused = False;

    if ((r = ICInputEvent(ccw->ccontrol.inputobj, event)) == 1 ||
	(sendback && !ccw->ccontrol.eventused &&
	 ICNumSegments(ccw->ccontrol.inputobj) == 0)) {
#else


    if ((r = ICInputEvent(ccw->ccontrol.inputobj, event)) == 1) {
#endif


	if (hascallback) {
	    TRACE(("call XtNunusedEventCallback\n"));
	    XtCallCallbackList(w, ccw->ccontrol.unusedeventcallback,
			       (XtPointer)event);
	} else if (ccw->ccontrol.sendbackKeyPress) {
	    Window savewin;
	    Window savesubwin;

	    TRACE(("sendback event to window 0x%lx\n", ccw->ccontrol.focuswindow));
	    savewin = event->xkey.window;
	    savesubwin = event->xkey.subwindow;
	    event->xkey.window = ccw->ccontrol.focuswindow;
	    event->xkey.subwindow = None;


	    XSendEvent(XtDisplay(w), event->xkey.window,
		       False, NoEventMask, event);

	    event->xkey.window = savewin;
	    event->xkey.subwindow = savesubwin;
	}
    }

    if (r < 0 || ccw->ccontrol.endnotify) {
	CControlEndConversion(w);
	XtCallCallbackList(w, ccw->ccontrol.endcallback, (XtPointer)False);
    }
}
