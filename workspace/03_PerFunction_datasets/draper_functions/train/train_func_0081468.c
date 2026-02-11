go_image_get_format_info (GOImageFormat format)
{
	if (format == GO_IMAGE_FORMAT_UNKNOWN)
		return NULL;
	if (format > GO_IMAGE_FORMAT_UNKNOWN)
		go_image_build_pixbuf_format_infos ();

	g_return_val_if_fail (format >= 0 &&
			      format <= GO_IMAGE_FORMAT_UNKNOWN + pixbuf_format_nbr, NULL);
	if (format < GO_IMAGE_FORMAT_UNKNOWN)
		return &image_format_infos[format];

	return &pixbuf_image_format_infos[format - PIXBUF_IMAGE_FORMAT_OFFSET];
}
