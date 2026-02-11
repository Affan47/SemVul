gkm_ssh_openssh_parse_public_key (gconstpointer input, gsize n_data,
                                  gcry_sexp_t *sexp, gchar **comment)
{
	EggBuffer buf;
	const guchar *at;
	guchar *decoded;
	gsize n_decoded;
	gsize offset;
	gchar *val;
	gboolean ret;
	gint state, algo;
	guint save;
	const guchar *data = input;

	g_return_val_if_fail (data, FALSE);
	g_return_val_if_fail (sexp, FALSE);


	for (;;) {

		while (n_data > 0 && g_ascii_isspace (data[0])) {
			++data;
			--n_data;
		}


		if (data[0] != '#')
			break;


		at = memchr (data, '\n', n_data);
		if (!at)
			return GKM_DATA_UNRECOGNIZED;
		at += 1;
		n_data -= (at - data);
		data = at;
	}


	at = memchr (data, '\n', n_data);
	if (at != NULL)
		n_data = at - data;


	at = memchr (data, ' ', n_data);
	if (!at) {
		g_message ("SSH public key missing space");
		return GKM_DATA_UNRECOGNIZED;
	}


	val = g_strndup ((gchar*)data, at - data);
	algo = keytype_to_algo (val);
	if (!algo) {

		if (atoi (val) == 0)
			g_message ("Unsupported or unknown SSH key algorithm: %s", val);
	}
	g_free (val);
	if (!algo)
		return GKM_DATA_UNRECOGNIZED;


	n_data -= (at - data);
	data = at;
	while (n_data > 0 && (data[0] == ' ' || data[0] == '\t')) {
		++data;
		--n_data;
	}


	at = memchr (data, ' ', n_data);
	if (at == NULL)
		at = data + n_data;


	save = state = 0;
	decoded = g_malloc (n_data * 3 / 4);
	n_decoded = g_base64_decode_step ((gchar*)data, n_data, decoded, &state, &save);


	egg_buffer_init_static (&buf, decoded, n_decoded);
	offset = 0;
	ret = read_public (&buf, &offset, sexp, NULL);
	g_free (decoded);
	if (!ret) {
		g_message ("failed to parse base64 part of SSH key");
		return GKM_DATA_FAILURE;
	}


	n_data -= (at - data);
	data = at;
	while (n_data > 0 && (data[0] == ' ' || data[0] == '\t')) {
		++data;
		--n_data;
	}


	if (comment)
		*comment = n_data ? g_strndup ((gchar*)data, n_data) : NULL;

	return GKM_DATA_SUCCESS;
}
