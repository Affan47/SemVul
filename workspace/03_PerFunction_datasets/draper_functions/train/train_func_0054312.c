getMWMHints(Window w)
{
    	Atom real_type; int real_format;
    	unsigned long items_read, items_left;
    	MwmHints *data;

    	if (XGetWindowProperty(dpy, w, atom_mwm_hints, 0L, 20L, False,
            wm->atom_mwm_hints, &real_type, &real_format, &items_read, &items_left,
            (unsigned char **) &data) == Success && items_read >= PropMwmHintsElements)
	{
        	return data;
	}
	else return NULL;
}
