send_url(request_rec *r, const char *const restrict uri, const char *const restrict command,
			const short html)
{
	const mu_config *const conf = (mu_config *)ap_get_module_config(r->per_dir_config, &musicindex_module);
	static char prefix[MAX_PREFIX];
	static char str_port[7], strtmp[6];
#ifdef BE_INSECURE
	char * restrict bufcoded, * restrict decoded;
#endif
	unsigned short l = 0;
	unsigned register i=0, j=6;


	if ((conf->iceserver) && !(conf->options & MI_RSS)) {

		strcpy(prefix, "http://");


		if (conf->iceserver[0] == ':')
			strcat(prefix, ap_get_server_name(r));

		strncat(prefix, conf->iceserver, MAX_PREFIX-8);
	}
	else {
		strcpy(prefix, ap_http_method(r));
		strcat(prefix, "://");

		if (REQUEST_USER(r)) {
#ifdef BE_INSECURE


			const char *const auth = apr_table_get(r->headers_in, "Authorization");
			if (auth) {
				bufcoded = strrchr(auth, ' ');
				bufcoded++;
				decoded = (char *)malloc(1 + apr_base64_decode_len(bufcoded));
				l = apr_base64_decode(decoded, bufcoded);
				strncat(prefix, decoded, l);
				free(decoded);
			}
#else
			strncat(prefix, REQUEST_USER(r), MAX_PREFIX-10);
#endif
			strcat(prefix, "@");
		}


		if (unlikely((strlen(prefix) + strlen(ap_get_server_name(r))) > MAX_PREFIX-10)) {

			mi_rerror("prefix too %s", "long");
			return;
		}


		strcat(prefix, ap_get_server_name(r));


		l = ap_get_server_port(r);
		while (--j && l) {
			strtmp[i++] = "0123456789"[l%10];
			l /= 10;
		}
		str_port[0] = ':';
		for (j=1; i; j++)
			str_port[j] = strtmp[--i];
		str_port[j] = '\0';
		strcat(prefix, str_port);
	}


	if (html)
		ap_rvputs(r, prefix, ap_escape_html(r->pool, ap_escape_uri(r->pool, uri)), NULL);
	else
		ap_rvputs(r, prefix, ap_escape_uri(r->pool, uri), NULL);
	if (command)
		ap_rputs(command, r);
}
