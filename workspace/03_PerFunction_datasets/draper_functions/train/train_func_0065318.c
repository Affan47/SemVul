check_dig_cred(dig_cred_t* _c)
{
	dig_err_t res = E_DIG_OK;


	if (_c->username.user.s == 0) res |= E_DIG_USERNAME;


	if (_c->realm.s == 0)  res |= E_DIG_REALM;


	if (_c->username.domain.s &&
	    ((_c->username.domain.len != _c->realm.len) ||
	     (strncmp(_c->username.domain.s, _c->realm.s,
		      _c->realm.len) != 0)))
	    res |= E_DIG_DOMAIN;


	if (_c->nonce.s == 0) res |= E_DIG_NONCE;


	if (_c->uri.s == 0) res |= E_DIG_URI;


	if (_c->response.s == 0) res |= E_DIG_RESPONSE;


	if ((_c->qop.qop_parsed == QOP_AUTH) || (_c->qop.qop_parsed == QOP_AUTHINT)) {

		if (_c->cnonce.s == 0) res |= E_DIG_CNONCE;

		if (_c->nc.s == 0) res |= E_DIG_NC;
	}

	return res;
}
