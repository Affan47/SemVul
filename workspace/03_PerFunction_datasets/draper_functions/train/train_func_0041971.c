make_default_format_string(scaffolding * dest, unsigned int precision) {
	char * newformat = NULL;
	const size_t post_dot_bytes_needed = ((precision == 0) ? 0 : (size_t)log10(precision)) + 1;

	if (HAS_RIGHT(dest) && CHECK_FLAG(dest->flags, FLAG_EQUAL_WIDTH)) {
		const char * const equal_width_base = "%%0%u.%uf";
		const int left_len = (dest->left < 0) + (size_t)log10(fabs(dest->left)) + 1;
		const int right_len = (dest->right < 0) + (size_t)log10(fabs(dest->right)) + 1;
		const unsigned int pre_dot_digits_wanted = ENUM_MAX(left_len, right_len);
		const unsigned int total_chars_wanted = pre_dot_digits_wanted + (precision ? 1 + precision : 0);
		const size_t pre_dot_bytes_needed = (size_t)log10(total_chars_wanted) + 1;
		const size_t base_bytes = strlen(equal_width_base)
			- strlen("%")
			- strlen("%u") + pre_dot_bytes_needed
			- strlen("%u") + post_dot_bytes_needed
			+ 1;
		newformat = (char *)malloc(base_bytes);
		if (! newformat)
		    return 0;
		sprintf(newformat, equal_width_base, total_chars_wanted, precision);
	} else {
		const char * const default_base = "%%.%uf";
		const size_t base_bytes = strlen(default_base)
			- strlen("%")
			- strlen("%u") + post_dot_bytes_needed
			+ 1;
		newformat = (char *)malloc(base_bytes);
		if (! newformat)
		    return 0;
		sprintf(newformat, default_base, precision);
	}

	if (! set_format_strdup(&(dest->format), newformat)) {
		free(newformat);
		return 0;
	}

	free(newformat);
	return 1;
}
