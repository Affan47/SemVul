SPF_record_compile_macro(SPF_server_t *spf_server,
								SPF_response_t *spf_response,
								SPF_macro_t **spf_macrop,
								const char *record)
{
ALIGN_DECL(
	char			 buf[sizeof(SPF_macro_t) + SPF_MAX_MOD_LEN];
);
	SPF_macro_t		*spf_macro = (SPF_macro_t *)ALIGNED_DECL(buf);
	SPF_data_t		*data;
	SPF_errcode_t	 err;
	size_t			 size;

	data = SPF_macro_data(spf_macro);
	spf_macro->macro_len = 0;

	err = SPF_c_parse_macro(spf_server, spf_response,
					data, &spf_macro->macro_len, SPF_MAX_MOD_LEN,
					record, strlen(record),
					SPF_E_BIG_MOD, TRUE);
	if (err != SPF_E_SUCCESS)
		return err;


	size = sizeof(SPF_macro_t) + spf_macro->macro_len;
	*spf_macrop = (SPF_macro_t *)malloc(size);
	if (!*spf_macrop)
		return SPF_E_NO_MEMORY;
	memcpy(*spf_macrop, ALIGNED_DECL(buf), size);

	return SPF_E_SUCCESS;
}
