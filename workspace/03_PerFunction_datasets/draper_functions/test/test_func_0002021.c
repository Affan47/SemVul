image_get_x11_screen_profile(ImageWindow *imd, guchar **screen_profile, gint *screen_profile_len)
{
	GdkScreen *screen = gtk_widget_get_screen(imd->widget);;
	GdkAtom    type   = GDK_NONE;
	gint       format = 0;

	return (gdk_property_get(gdk_screen_get_root_window(screen),
				 gdk_atom_intern ("_ICC_PROFILE", FALSE),
				 GDK_NONE,
				 0, 64 * 1024 * 1024, FALSE,
				 &type, &format, screen_profile_len, screen_profile) && *screen_profile_len > 0);
}
