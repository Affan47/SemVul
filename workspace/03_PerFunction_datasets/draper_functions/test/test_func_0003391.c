mono_assembly_try_decode_skip_verification (const char *p, const char *endn)
{
	int i, j, num, len, params_len;

	if (*p == MONO_DECLSEC_FORMAT_10) {
		gsize read, written;
		char *res = g_convert (p, endn - p, "UTF-8", "UTF-16LE", &read, &written, NULL);
		if (res) {
			gboolean found = strstr (res, SKIP_VISIBILITY_XML_ATTRIBUTE) != NULL;
			g_free (res);
			return found;
		}
		return FALSE;
	}
	if (*p++ != MONO_DECLSEC_FORMAT_20)
		return FALSE;


	num = mono_metadata_decode_value (p, &p);
	for (i = 0; i < num; ++i) {
		gboolean is_valid = FALSE;
		gboolean abort_decoding = FALSE;


		len =  mono_metadata_decode_value (p, &p);


		is_valid = len >= SKIP_VISIBILITY_ATTRIBUTE_SIZE && !memcmp (p, SKIP_VISIBILITY_ATTRIBUTE_NAME, SKIP_VISIBILITY_ATTRIBUTE_SIZE);

		p += len;


		params_len =  mono_metadata_decode_value (p, &p);
		if (is_valid) {
			const char *params_end = p + params_len;


			len = mono_metadata_decode_value (p, &p);

			for (j = 0; j < len; ++j) {
				if (mono_assembly_try_decode_skip_verification_param (p, &p, &abort_decoding))
					return TRUE;
				if (abort_decoding)
					break;
			}
			p = params_end;
		} else {
			p += params_len;
		}
	}

	return FALSE;
}
