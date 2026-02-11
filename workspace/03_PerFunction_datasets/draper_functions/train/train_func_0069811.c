showmsgrfc822_header(const char *output_chset,
				const char *p, const char *chset)
{
	struct filter_info info;

	unicode_char *uc;
	size_t ucsize;

	int conv_err;

	if (libmail_u_convert_tou_tobuf(p, strlen(p), chset,
					&uc, &ucsize,
					&conv_err))
	{
		conv_err=1;
		uc=NULL;
	}

	filter_start(&info, output_chset, showmsgrfc822_headerp, NULL);

	if (uc)
	{
		filter(&info, uc, ucsize);
		free(uc);
	}
	filter_end(&info);

	if (info.conversion_error)
		conv_err=1;

	return conv_err;
}
