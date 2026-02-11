handleExposeEvent(XEvent *ev)
{
	BaseMenu* mu = window_menu->findMenu(ev->xexpose.window);

	if(!mu)
		mu = icon_menu->findMenu(ev->xexpose.window);

	if(mu)
		mu->handleExposeEvent(&ev->xexpose);
	else
	{
		Client* c = findClient(ev->xexpose.window);

		if(c)
			c->handleExposeEvent(&ev->xexpose);
	}
}
