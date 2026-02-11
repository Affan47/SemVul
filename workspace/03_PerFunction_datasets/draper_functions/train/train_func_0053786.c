GMT_freeshorthand (void) {
	GMT_LONG i;

	if (GMT_n_file_suffix == 0) return;

	for (i = 0; i < GMT_n_file_suffix; i++) free ((void *)GMT_file_suffix[i]);
	GMT_free ((void *)GMT_file_id);
	GMT_free ((void *)GMT_file_scale);
	GMT_free ((void *)GMT_file_offset);
	GMT_free ((void *)GMT_file_nan);
	GMT_free ((void *)GMT_file_suffix);
}
