tls_success(tls_session_t *ssn, REQUEST *request)
{
	VALUE_PAIR *vp, *vps = NULL;
	fr_tls_server_conf_t *conf;

	conf = (fr_tls_server_conf_t *)SSL_get_ex_data(ssn->ssl, FR_TLS_EX_INDEX_CONF);
	rad_assert(conf != NULL);


	if ((!ssn->allow_session_resumption) ||
	    (((vp = pairfind(request->config_items, 1127, 0)) != NULL) &&
	     (vp->vp_integer == 0))) {
		SSL_CTX_remove_session(ssn->ctx,
				       ssn->ssl->session);
		ssn->allow_session_resumption = 0;


		if (SSL_session_reused(ssn->ssl)) {
			RDEBUG("FAIL: Forcibly stopping session resumption as it is not allowed.");
			return -1;
		}


	} else if (!SSL_session_reused(ssn->ssl)) {
		size_t size;
		char buffer[2 * MAX_SESSION_SIZE + 1];

		size = ssn->ssl->session->session_id_length;
		if (size > MAX_SESSION_SIZE) size = MAX_SESSION_SIZE;

		fr_bin2hex(ssn->ssl->session->session_id, buffer, size);


		vp = paircopy2(request->reply->vps, PW_USER_NAME, 0);
		if (vp) pairadd(&vps, vp);

		vp = paircopy2(request->packet->vps, PW_STRIPPED_USER_NAME, 0);
		if (vp) pairadd(&vps, vp);

		vp = paircopy2(request->reply->vps, PW_CACHED_SESSION_POLICY, 0);
		if (vp) pairadd(&vps, vp);

		if (vps) {
			RDEBUG2("Saving session %s vps %p in the cache", buffer, vps);
			SSL_SESSION_set_ex_data(ssn->ssl->session,
						FR_TLS_EX_INDEX_VPS, vps);
		} else {
			RDEBUG2("WARNING: No information to cache: session caching will be disabled for session %s", buffer);
			SSL_CTX_remove_session(ssn->ctx,
					       ssn->ssl->session);
		}


	} else {
		size_t size;
		char buffer[2 * MAX_SESSION_SIZE + 1];

		size = ssn->ssl->session->session_id_length;
		if (size > MAX_SESSION_SIZE) size = MAX_SESSION_SIZE;

		fr_bin2hex(ssn->ssl->session->session_id, buffer, size);


		vp = SSL_SESSION_get_ex_data(ssn->ssl->session,
					     FR_TLS_EX_INDEX_VPS);
		if (!vp) {
			RDEBUG("WARNING: No information in cached session %s", buffer);
			return -1;

		} else {
			RDEBUG("Adding cached attributes for session %s vps %p to the reply:", buffer, vp);
			debug_pair_list(vp);
			pairadd(&request->reply->vps, paircopy(vp));


			vp = pairmake("EAP-Session-Resumed", "1", T_OP_SET);
			if (vp) pairadd(&request->packet->vps, vp);
		}
	}

	return 0;
}
