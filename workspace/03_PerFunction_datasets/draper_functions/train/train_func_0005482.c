kill_xsetroot_data_1 (Display *dpy, Window window,
                      Atom prop, const char *atom_name,
                      Bool verbose_p)
{
  Atom type;
  int format;
  unsigned long nitems, bytesafter;
  unsigned char *dataP = 0;


  if (XGetWindowProperty (dpy, window, prop, 0, 1,
			  True, AnyPropertyType, &type, &format, &nitems,
			  &bytesafter, &dataP)
      == Success
      && type != None)
    {
      Pixmap *pixP = (Pixmap *) dataP;
      if (pixP && *pixP && type == XA_PIXMAP && format == 32 &&
	  nitems == 1 && bytesafter == 0)
	{
	  if (verbose_p)
	    fprintf (stderr, "%s: destroying %s data (0x%lX).\n",
		     blurb(), atom_name, *pixP);
	  safe_XKillClient (dpy, *pixP);
	}
      else
	fprintf (stderr,
                 "%s: deleted unrecognised %s property: \n"
                 "\t%lu, %lu; type: %lu, format: %d, "
                 "nitems: %lu, bytesafter %ld\n",
		 blurb(), atom_name,
                 (unsigned long) pixP, (pixP ? *pixP : 0), type,
		 format, nitems, bytesafter);
    }
}
