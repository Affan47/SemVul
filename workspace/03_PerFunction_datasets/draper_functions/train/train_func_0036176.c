_expand_filename(const char *template, const char *vg_name,
			      char **last_filename)
{
	char *filename;

	if (security_level())
		return dm_strdup(template);

	if (!(filename = dm_malloc(PATH_MAX))) {
		log_error("Failed to allocate filename.");
		return NULL;
	}

	if (dm_snprintf(filename, PATH_MAX, template, vg_name) < 0) {
		log_error("Error processing filename template %s",
			   template);
		dm_free(filename);
		return NULL;
	}
	if (*last_filename && !strncmp(*last_filename, filename, PATH_MAX)) {
		log_error("VGs must be backed up into different files. "
			  "Use %%s in filename for VG name.");
		dm_free(filename);
		return NULL;
	}

	dm_free(*last_filename);
	*last_filename = filename;

	return filename;
}
