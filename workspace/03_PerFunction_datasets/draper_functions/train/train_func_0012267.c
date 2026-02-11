doResize(int& new_w, int& new_h)
    {

	if (new_w != m_w)
	    new_w = (new_w + 7) & ~7;
	if (new_h != m_h)

	    new_h = (new_h + 1) & ~1;

	if (!m_bResizeEnabled)
	{
	    AVM_WRITE(__RENDERER__, "Resize is unsupported for RGB Direct mode!\n");

	    new_w = m_w;
	    new_h = m_h;
            return -1;
	}

	if (new_w < 8 || new_h < 2)
	    return -1;

	if (pic_w != new_w || pic_h != new_h)
	{
	    if (image && screen && image->Data() == screen->pixels)
	    {
		AVM_WRITE(__RENDERER__, "Resize is unsupported for RGB Direct mode!\n");
		new_w = m_w;
		new_h = m_h;
		return -1;
		CImage* ci = new CImage(image);
		image->Release();

		image = ci;
	    }
	    pic_w = new_w;
	    pic_h = new_h;
	    cliprect.x = cliprect.y = 0;
	    cliprect.w = (Uint16)new_w;
	    cliprect.h = (Uint16)new_h;

	    screen = SDL_SetVideoMode(pic_w, pic_h + m_sub, 0, fs);

	    delete[] convbuf;
	    convbuf = 0;
	}
	return 0;
    }
