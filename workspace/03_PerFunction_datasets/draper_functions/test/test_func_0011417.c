handleConfigureRequestEvent(XEvent *ev)
{
	Client* c = findClient(ev->xconfigurerequest.window);

	if(c)
		c->handleConfigureRequest(&ev->xconfigurerequest);
	else
	{


		XWindowChanges wc;

	        wc.x = ev->xconfigurerequest.x;
		wc.y = ev->xconfigurerequest.y;
		wc.width = ev->xconfigurerequest.width;
		wc.height = ev->xconfigurerequest.height;
	    	wc.sibling = ev->xconfigurerequest.above;
	    	wc.stack_mode = ev->xconfigurerequest.detail;
		XConfigureWindow(dpy, ev->xconfigurerequest.window, ev->xconfigurerequest.value_mask, &wc);
	}
}
