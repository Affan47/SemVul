nemo_icon_info_get_pixbuf (NemoIconInfo *icon)
{
	GdkPixbuf *res;

	res = nemo_icon_info_get_pixbuf_nodefault (icon);
	if (res == NULL) {
		res = gdk_pixbuf_new_from_data (nemo_default_file_icon,
						GDK_COLORSPACE_RGB,
						TRUE,
						8,
						nemo_default_file_icon_width,
						nemo_default_file_icon_height,
						nemo_default_file_icon_width * 4,
						NULL,
						NULL);
	}

	return res;
}
