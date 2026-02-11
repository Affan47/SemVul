free_colorset_background(colorset_t *cs, Bool do_free_args)
{
	if (cs->picture != NULL)
	{
		if (cs->picture->picture != cs->pixmap)
		{
			add_to_junk(cs->pixmap);
		}
		SafeDestroyPicture(dpy, cs->picture);
		cs->picture = NULL;
		cs->pixmap = None;
		cs->alpha_pixmap = None;
	}
	if (cs->pixmap && cs->pixmap != ParentRelative &&
	    cs->pixmap != root_pic.pixmap && cs->pixmap != root_pic.old_pixmap)
	{
		add_to_junk(cs->pixmap);
	}
	cs->pixmap = None;
	if (cs->mask)
	{
		add_to_junk(cs->mask);
		cs->mask = None;
	}
	if (cs->alpha_pixmap)
	{
		add_to_junk(cs->alpha_pixmap);
		cs->alpha_pixmap = None;
	}
	if (cs->pixels && cs->nalloc_pixels)
	{
		PictureFreeColors(
			dpy, Pcmap, cs->pixels, cs->nalloc_pixels, 0, False);
		free(cs->pixels);
		cs->pixels = NULL;
		cs->nalloc_pixels = 0;
	}
	if (do_free_args)
	{
		if (cs->pixmap_args != NULL)
		{
			free(cs->pixmap_args);
			cs->pixmap_args = NULL;
		}
		if (cs->gradient_args != NULL)
		{
			free(cs->gradient_args);
			cs->gradient_args = NULL;
		}
		cs->is_maybe_root_transparent = False;
		cs->pixmap_type = 0;
	}
}
