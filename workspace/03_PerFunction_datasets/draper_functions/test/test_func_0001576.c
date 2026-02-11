plot_image_set_wcs(plotimage_t* args, const char* filename, int ext) {
	if (args->wcs)
		anwcs_free(args->wcs);
	if (streq(filename, "none")) {
		args->wcs = NULL;
	} else {
		args->wcs = anwcs_open(filename, ext);
		if (!args->wcs) {
			ERROR("Failed to read WCS file \"%s\"", filename);
			return -1;
		}
		if (log_get_level() >= LOG_VERB) {
			logverb("Set image WCS to:");
			anwcs_print(args->wcs, stdout);
		}
	}
	return 0;
}
