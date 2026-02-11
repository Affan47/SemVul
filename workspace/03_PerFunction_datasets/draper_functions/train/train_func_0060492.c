DAProcessEventForWindow(Window window, XEvent *event)
{
    extern char *progName;

    if (event->xany.window != window)
	return False;

    switch (event->type) {
	case ClientMessage:
	    if (event->xclient.data.l[0] != WM_DELETE_WINDOW) {
		break;
	    }

	case DestroyNotify:
	    if (d_callbacks.destroy)
		(*d_callbacks.destroy)();

	    XCloseDisplay(DADisplay);
#ifdef DEBUG
	    fprintf(stderr, "%s: DestroyNotify\n", progName);
#endif

	    exit(0);
	    break;
	case ButtonPress:
	    if (d_callbacks.buttonPress)
		(*d_callbacks.buttonPress)(event->xbutton.button,
					   event->xbutton.state,
					   event->xbutton.x,
					   event->xbutton.y);
	    break;
	case ButtonRelease:
	    if (d_callbacks.buttonRelease)
		(*d_callbacks.buttonRelease)(event->xbutton.button,
					     event->xbutton.state,
					     event->xbutton.x,
					     event->xbutton.y);
	    break;
	case MotionNotify:
	    if (d_callbacks.motion)
		(*d_callbacks.motion)(event->xmotion.x,
				      event->xmotion.y);
	    break;
	case EnterNotify:
	    if (d_callbacks.enter)
		(*d_callbacks.enter)();
	    break;
	case LeaveNotify:
	    if (d_callbacks.leave)
		(*d_callbacks.leave)();
	    break;
	default:
	    return False;
    }

    return True;
}
