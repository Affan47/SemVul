mbfl_convert_filter_strcat(mbfl_convert_filter *filter, const unsigned char *p)
{
	int c;

	while ((c = *p++) != '\0') {
		if ((*filter->filter_function)(c, filter) < 0) {
			return -1;
		}
	}

	return 0;
}
