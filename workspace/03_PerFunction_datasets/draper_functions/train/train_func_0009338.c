header_fmt_append_full(header_fmt_t *hf, const char *str,
	const char *separator, size_t slen, size_t sslen)
{
	size_t len, curlen;
	gsize gslen;
	bool success;

	header_fmt_check(hf);
	g_assert(size_is_non_negative(slen));
	g_assert((size_t)-1 == sslen || size_is_non_negative(sslen));

	if (hf->empty)
		return FALSE;

	gslen = str_len(hf->header);
	len = strlen(str);
	curlen = hf->current_len;
	g_assert(size_is_non_negative(curlen));

	g_assert(len <= INT_MAX);

	if (
		size_saturate_add(curlen, size_saturate_add(len, slen)) >
			UNSIGNED(hf->maxlen)
	) {


		if (separator != NULL && hf->data_emitted) {
			sslen = (size_t)-1 != sslen ? sslen :
				stripped_strlen(separator, slen);
			str_cat_len(hf->header, separator, sslen);
		}

		str_cat(hf->header, "\r\n\t");
		curlen = 1;
	} else if (hf->data_emitted) {
		str_cat(hf->header, separator);
		curlen += slen;
	}

	str_cat(hf->header, str);


	if (str_len(hf->header) + sizeof("\r\n") > hf->max_size) {
		success = FALSE;
		str_setlen(hf->header, gslen);
	} else {
		success = TRUE;
		hf->data_emitted = TRUE;
		hf->current_len = curlen + len;
	}

	g_assert(str_len(hf->header) + sizeof("\r\n") <= hf->max_size);

	return success;
}
