brasero_image_format_get_complement (BraseroImageFormat format,
				     const gchar *path)
{
	gchar *retval = NULL;

	if (format == BRASERO_IMAGE_FORMAT_CLONE) {


		if (g_str_has_suffix (path, ".toc"))
			retval = g_strndup (path, strlen (path) - 4);
	}
	else if (format == BRASERO_IMAGE_FORMAT_CUE) {

		retval = brasero_image_format_get_cue_file_complement (path);
	}
	else if (format == BRASERO_IMAGE_FORMAT_CDRDAO) {

		retval = brasero_image_format_get_toc_file_complement (path);
	}
	else
		retval = NULL;

	return retval;
}
