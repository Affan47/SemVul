mbfl_filt_conv_html_dec_dtor(mbfl_convert_filter *filter)
{
	filter->status = 0;
	if (filter->opaque)
	{
		mbfl_free((void*)filter->opaque);
	}
	filter->opaque = NULL;
}
