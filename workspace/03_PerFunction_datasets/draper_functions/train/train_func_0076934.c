mbfl_filt_conv_ucs2le_wchar(int c, mbfl_convert_filter *filter)
{
	int n;

	if (filter->status == 0) {
		filter->status = 1;
		n = c & 0xff;
		filter->cache = n;
	} else {
		filter->status = 0;
		n = ((c & 0xff) << 8) | filter->cache;
		CK((*filter->output_function)(n, filter->data));
	}
	return c;
}
