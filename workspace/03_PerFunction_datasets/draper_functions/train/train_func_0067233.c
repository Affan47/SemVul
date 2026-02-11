handleButtonPressEvent(XEvent *ev)
{
	if (ev->xbutton.window == root)
	{
		switch (ev->xbutton.button)
		{
			case Button1:
				if(icon_menu->isVisible())
					icon_menu->hide();
			break;

			case Button2:
				if(icon_menu->getItemCount())
				{
					if(icon_menu->isVisible())
						icon_menu->hide();
					else
						icon_menu->show();
				}
			break;

			case Button3:
				forkExec(opt_new1);

				if(icon_menu->isVisible())
					icon_menu->hide();
			break;
	        }
	}
	else
	{
		Client* c = findClient(ev->xbutton.window);

		if(c && c->hasWindowDecorations())
		{
			if( (ev->xbutton.button == Button1)
			    &&
			    (ev->xbutton.type==ButtonPress)
			    &&
			    (ev->xbutton.state==Mod1Mask)
			    &&
			    (c->getFrameWindow() == ev->xbutton.window)
			   )
			{
				if (!Grab(c->getFrameWindow(), PointerMotionMask|ButtonReleaseMask, wm->getMoveCursor())) return;
			}
		}

		switch (focus_model)
		{
			case FOCUS_FOLLOW:
			case FOCUS_SLOPPY:
				if(c)
				{
					c->handleButtonEvent(&ev->xbutton);
					focused_client = c;
				}
			break;

			case FOCUS_CLICK:

				if(c && c != focused_client)
				{
					XSetInputFocus(dpy, c->getAppWindow(), RevertToNone, CurrentTime);
					focused_client = c;
				}


				if(c && c == focused_client)
					c->handleButtonEvent(&ev->xbutton);
			break;
		}

		BaseMenu* mu = window_menu->findMenu(ev->xbutton.window);

		if(!mu)
			mu = icon_menu->findMenu(ev->xbutton.window);

		if(mu)
			mu->handleButtonPressEvent(&ev->xbutton);
	}

	if(ev->xbutton.window==root)
		XSendEvent(dpy, _button_proxy_win, False, SubstructureNotifyMask, ev);

}
