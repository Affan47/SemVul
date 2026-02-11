generate_response (struct _DigestChallenge *challenge,
                   const gchar *host,
                   const gchar *protocol,
                   const gchar *user,
                   const gchar *passwd)
{
	struct _DigestResponse *resp;
	struct _DigestURI *uri;
	GChecksum *checksum;
	guint8 *digest;
	gsize length;
	gchar *bgen;

	length = g_checksum_type_get_length (G_CHECKSUM_MD5);
	digest = g_alloca (length);

	resp = g_new0 (struct _DigestResponse, 1);
	resp->username = g_strdup (user);

	if (challenge->realms && challenge->realms->len > 0)
		resp->realm = g_strdup (challenge->realms->pdata[0]);
	else
		resp->realm = g_strdup ("");

	resp->nonce = g_strdup (challenge->nonce);


	bgen = g_strdup_printf (
		"%p:%lu:%lu",
		(gpointer) resp,
		(gulong) getpid (),
		(gulong) time (NULL));
	checksum = g_checksum_new (G_CHECKSUM_MD5);
	g_checksum_update (checksum, (guchar *) bgen, -1);
	g_checksum_get_digest (checksum, digest, &length);
	g_checksum_free (checksum);
	g_free (bgen);


	resp->cnonce = g_base64_encode ((guchar *) digest, 8);


	g_strlcpy (resp->nc, "00000001", sizeof (resp->nc));


	resp->qop = QOP_AUTH;


	uri = g_new0 (struct _DigestURI, 1);
	uri->type = g_strdup (protocol);
	uri->host = g_strdup (host);
	uri->name = NULL;
	resp->uri = uri;


	if (challenge->charset) {


		resp->charset = g_strdup (challenge->charset);
	}

	resp->cipher = CIPHER_INVALID;
	if (resp->qop == QOP_AUTH_CONF) {

		resp->cipher = CIPHER_INVALID;
	}


	resp->authzid = NULL;

	compute_response (resp, passwd, TRUE, (guchar *) resp->resp);

	return resp;
}
