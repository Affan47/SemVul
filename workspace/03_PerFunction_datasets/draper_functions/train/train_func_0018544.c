doResize(int& new_w, int& new_h)
    {
	if (new_w != m_w)
	    new_w = (new_w + 7) & ~7;
	if (new_h != m_h)
	    new_h = (new_h + 1) & ~1;

	if (new_w >= 8 && new_h >= 2
	    && (pic_w != new_w || pic_h != new_h))
	{
#if _SDL_VER > 1103
	    fs |= SDL_RESIZABLE;
#endif
	    screen = SDL_SetVideoMode(new_w, new_h + m_sub, 0, fs);
	    if (screen) {
		pic_w = new_w;
		pic_h = new_h;
                return 0;
	    }
	    screen = SDL_SetVideoMode(pic_w, pic_h + m_sub, 0, fs);
	}

	new_w = pic_w;
	new_h = pic_h;

	return -1;
    }
}
