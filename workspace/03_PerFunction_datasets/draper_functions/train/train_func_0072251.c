create_gnutls_handle(apr_pool_t * pool, conn_rec * c)
{
	mgs_handle_t *ctxt;
	mgs_srvconf_rec *sc =
	    (mgs_srvconf_rec *) ap_get_module_config(c->base_server->
						     module_config,
						     &gnutls_module);

	_gnutls_log(debug_log_fp, "%s: %d\n", __func__, __LINE__);
	ctxt = apr_pcalloc(pool, sizeof(*ctxt));
	ctxt->c = c;
	ctxt->sc = sc;
	ctxt->status = 0;

	ctxt->input_rc = APR_SUCCESS;
	ctxt->input_bb = apr_brigade_create(c->pool, c->bucket_alloc);
	ctxt->input_cbuf.length = 0;

	ctxt->output_rc = APR_SUCCESS;
	ctxt->output_bb = apr_brigade_create(c->pool, c->bucket_alloc);
	ctxt->output_blen = 0;
	ctxt->output_length = 0;

	gnutls_init(&ctxt->session, GNUTLS_SERVER);
	if (session_ticket_key.data != NULL && ctxt->sc->tickets != 0)
		gnutls_session_ticket_enable_server(ctxt->session,
						    &session_ticket_key);


	gnutls_protocol_set_priority(ctxt->session, protocol_priority);

	gnutls_handshake_set_post_client_hello_function(ctxt->session,
							mgs_select_virtual_server_cb);

	mgs_cache_session_init(ctxt);

	return ctxt;
}
