defaultIcon()
{
	if (!_default_icon)
	{
		GdkPixbuf *img = gdk_pixbuf_new_from_xpm_data((const char**)_default_trayicon);
		_default_icon = new gPicture(img);
	}

	return _default_icon;
}
