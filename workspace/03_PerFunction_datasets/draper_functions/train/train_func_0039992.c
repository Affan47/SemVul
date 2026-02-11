tls_init(struct gnutella_socket *s)
{


	static const char prio_want[] = "NORMAL:+ANON-DH:-ARCFOUR-40:-COMP-DEFLATE";

	static const char prio_must[] = "NORMAL:+ANON-DH:-ARCFOUR-40";
	const bool server = SOCK_CONN_INCOMING == s->direction;
	struct tls_context *ctx;
	const char *fn;
	int e;

#define TRY(function) (fn = (#function)), e = function

	socket_check(s);

	WALLOC0(ctx);
	ctx->s = s;
	s->tls.ctx = ctx;

	if (
		TRY(gnutls_init)(&ctx->session, server ? GNUTLS_SERVER : GNUTLS_CLIENT)
	) {
		ctx->session = NULL;
		goto failure;
	}

	if (TRY(gnutls_priority_set_direct)(ctx->session, prio_want, NULL)) {
		const char *error;
		if (TRY(gnutls_priority_set_direct)(ctx->session, prio_must, &error)) {
			g_warning("%s() failed at \"%s\"", fn, error);
			goto failure;
		}
	}

	if (TRY(gnutls_credentials_set)(ctx->session,
			GNUTLS_CRD_CERTIFICATE, cert_cred))
		goto failure;

	gnutls_dh_set_prime_bits(ctx->session, TLS_DH_BITS);

#ifdef USE_TLS_CUSTOM_IO
	gnutls_transport_set_ptr(ctx->session, s);
	gnutls_transport_set_push_function(ctx->session, tls_push);
	gnutls_transport_set_pull_function(ctx->session, tls_pull);
#if !HAS_TLS(2, 12)


	gnutls_transport_set_lowat(ctx->session, 0);
#endif
#else
	g_assert(is_valid_fd(s->file_desc));
	gnutls_transport_set_ptr(ctx->session, int_to_pointer(s->file_desc));
#endif

	if (server) {
		if (TRY(gnutls_anon_allocate_server_credentials)(&ctx->server_cred))
			goto failure;

		gnutls_anon_set_server_dh_params(ctx->server_cred, get_dh_params());

		if (TRY(gnutls_credentials_set)(ctx->session,
				GNUTLS_CRD_ANON, ctx->server_cred))
			goto failure;

	} else {
		if (TRY(gnutls_anon_allocate_client_credentials)(&ctx->client_cred))
			goto failure;

		if (TRY(gnutls_credentials_set)(ctx->session,
				GNUTLS_CRD_ANON, ctx->client_cred))
			goto failure;
	}

	return 0;

failure:
	g_warning("%s() failed: %s", EMPTY_STRING(fn), gnutls_strerror(e));
	tls_free(s);
	return -1;
#undef TRY
}
