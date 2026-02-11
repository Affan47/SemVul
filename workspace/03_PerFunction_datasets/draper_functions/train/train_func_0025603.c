ToggleFullscreen(bool maximize = false)
    {
	if (dga)
	    return -1;
	Lock();

	if (!(screen->flags & SDL_FULLSCREEN))
	{
	    m_Mouse.Store();
	    if (maximize && m_bResizeEnabled)
	    {
		int w = max_w = pic_w;
		int h = pic_h + m_sub;
		max_h = pic_h;
		GetModeLine(w, h);

		float ratio_x = (float)w / (float)pic_w;
		float ratio_y = (float)(h - m_sub) / (float)pic_h;
		float ratio = (ratio_x < ratio_y) ? ratio_x : ratio_y;
		w = (int) rint(ratio * (float)pic_w);
		h = (int) rint(ratio * (float)pic_h);
		if (pic_w != w || pic_h != h)
		{


		    if (doResize(w, h) < 0)
			max_w = max_h = 0;
		}
	    }
	}
#if _SDL_VER > 1102
	SDL_WM_ToggleFullScreen(screen);
	fs = screen->flags & SDL_FULLSCREEN;
#else
	screen->flags ^= SDL_FULLSCREEN;
	fs = screen->flags & SDL_FULLSCREEN;
	if (fs && max_w > 0)
	    XMoveWindow(dpy, info.info.x11.window, 0, 0);
#endif
	if (!fs)
	{
	    m_Mouse.Restore();
	    if (max_w && max_h)
		doResize(max_w, max_h);
	    max_w = max_h = 0;
	}
	m_Mouse.Off();
	Unlock();
	Refresh();
	return fs;
    }
