ReadBitmapFileDialog(char *FileName, gn_bmp *bitmap, gn_phone *info)
{
	gn_error error;

	error = gn_file_bitmap_read(FileName, bitmap, info);
	switch (error) {
	case GN_ERR_NONE:
		break;
	default:
		fprintf(stderr, _("Error while reading file \"%s\": %s\n"), FileName, gn_error_print(error));
		break;
	}
	return error;
}
