handleXEvents() {
    if (XPending(display()) > 0) {
        XEvent xev;

        XNextEvent(display(), &xev);
#ifdef DEBUG
        xeventcount++;
#endif


        saveEventTime(xev);

#ifdef DEBUG
        DBG logEvent(xev);
#endif
        if (filterEvent(xev)) {
            ;
        } else {
            int ge = (xev.type == ButtonPress ||
                      xev.type == ButtonRelease ||
                      xev.type == MotionNotify ||
                      xev.type == KeyPress ||
                      xev.type == KeyRelease

) ? 1 : 0;

            fReplayEvent = false;

            if (fPopup && ge) {
                handleGrabEvent(fPopup, xev);
            } else if (fGrabWindow && ge) {
                handleGrabEvent(fGrabWindow, xev);
            } else {
                handleWindowEvent(xev.xany.window, xev);
            }
            if (fGrabWindow) {
                if (xev.type == ButtonPress || xev.type == ButtonRelease || xev.type == MotionNotify)
                {
                    if (!fReplayEvent) {
                        XAllowEvents(xapp->display(), SyncPointer, CurrentTime);
                    }
                }
            }
        }
        XFlush(display());
        return true;
    }
    return false;
}
