murrine_widget_is_rgba (GtkWidget *widget)
{
	boolean use_rgba = FALSE;
	GdkScreen *screen;

	if (widget)
		screen = gtk_widget_get_screen (widget);
	else
		return use_rgba;

#ifdef HAVE_RGBA
	if (gdk_screen_is_composited(screen))
	{
		GdkVisual *visual = gtk_widget_get_visual (widget);
		if (visual->depth == 32 && (visual->red_mask   == 0xff0000 &&
		                            visual->green_mask == 0x00ff00 &&
		                            visual->blue_mask  == 0x0000ff))
			use_rgba = TRUE;
	}
#endif

	return use_rgba;
}
