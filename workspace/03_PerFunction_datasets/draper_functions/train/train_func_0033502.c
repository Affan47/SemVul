handleDestroyNotifyEvent(XEvent *ev)
{
	Client* c = findClient(ev->xdestroywindow.window);

	if(c)
	{
		c->handleDestroyEvent(&ev->xdestroywindow);

		focused_client = NULL;
	}
}
