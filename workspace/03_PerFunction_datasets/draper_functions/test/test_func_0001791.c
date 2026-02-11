MotionEH(PLStream *pls, XEvent *event)
{
    XwDev *dev = (XwDev *) pls->dev;
    XMotionEvent *motionEvent = (XMotionEvent *) event;

    if (dev->drawing_xhairs) {
	DrawXhairs(pls, motionEvent->x, motionEvent->y);
    }
}
