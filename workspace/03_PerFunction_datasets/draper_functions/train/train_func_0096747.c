print_cred(dig_cred_t* _c)
{
	printf("===Digest credentials===\n");
	if (_c) {
		printf("Username\n");
		printf("+--whole  = \'%.*s\'\n", _c->username.whole.len, _c->username.whole.s);
		printf("+--user   = \'%.*s\'\n", _c->username.user.len, _c->username.user.s);
		printf("\\--domain = \'%.*s\'\n", _c->username.domain.len, _c->username.domain.s);
		printf("Realm     = \'%.*s\'\n", _c->realm.len, _c->realm.s);
		printf("Nonce     = \'%.*s\'\n", _c->nonce.len, _c->nonce.s);
		printf("URI       = \'%.*s\'\n", _c->uri.len, _c->uri.s);
		printf("Response  = \'%.*s\'\n", _c->response.len, _c->response.s);
		printf("Algorithm = \'%.*s\'\n", _c->alg.alg_str.len, _c->alg.alg_str.s);
		printf("\\--parsed = ");

		switch(_c->alg.alg_parsed) {
		case ALG_UNSPEC:  printf("ALG_UNSPEC\n");  break;
		case ALG_MD5:     printf("ALG_MD5\n");     break;
		case ALG_MD5SESS: printf("ALG_MD5SESS\n"); break;
		case ALG_OTHER:   printf("ALG_OTHER\n");   break;
		}

		printf("Cnonce    = \'%.*s\'\n", _c->cnonce.len, _c->cnonce.s);
		printf("Opaque    = \'%.*s\'\n", _c->opaque.len, _c->opaque.s);
		printf("QOP       = \'%.*s\'\n", _c->qop.qop_str.len, _c->qop.qop_str.s);
		printf("\\--parsed = ");

		switch(_c->qop.qop_parsed) {
		case QOP_UNSPEC:  printf("QOP_UNSPEC\n");  break;
		case QOP_AUTH:    printf("QOP_AUTH\n");    break;
		case QOP_AUTHINT: printf("QOP_AUTHINT\n"); break;
		case QOP_OTHER:   printf("QOP_OTHER\n");   break;
		}
		printf("NC        = \'%.*s\'\n", _c->nc.len, _c->nc.s);
	}
	printf("===/Digest credentials===\n");
}
