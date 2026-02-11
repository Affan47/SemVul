kbd_scroll_viewport_AC(Widget widget,  XEvent *event,
		       String *params, Cardinal *num_params)
{
    XtOrientation  ori;
    long           dir, percent;
    Dimension      length = 0;

    if (2 != *num_params) {
	fprintf(stderr,"KbdScroll: wrong number of arguments\n");
	return;
    }

    if (XtClass(widget) != scrollbarWidgetClass) {
	fprintf(stderr,"KbdScroll: not a scrollbar\n");
	return;
    }

    XtVaGetValues(widget,XtNorientation,&ori,NULL);
    XtVaGetValues(widget,(ori == XtorientVertical) ? XtNheight : XtNwidth,
		  &length,NULL);


    if (0 == strcasecmp(params[0],"left") ||
	0 == strcasecmp(params[0],"up")) {
	dir = -1;
    } else if (0 == strcasecmp(params[0],"right") ||
	       0 == strcasecmp(params[0],"down")) {
	dir = 1;
    } else {
	fprintf(stderr,"KbdScroll: what is %s?\n",params[0]);
	return;
    }


    percent = atoi(params[1]);
    if (percent <= 0 || percent > 100) {
	fprintf(stderr,"KbdScroll: invalid value: %s\n",params[1]);
	return;
    }
#if 0
    fprintf(stderr,"KbdScroll: %d %d %d => %d\n",
	    percent,length,dir,(dir*percent*length/100));
#endif
    XtCallCallbacks(widget, XtNscrollProc,
		    (XtPointer)(dir*percent*length/100));
}
