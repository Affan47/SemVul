parse_digest_params(str* _s, dig_cred_t* _c)
{
	char* comma;

	do {

		if (parse_digest_param(_s, _c) < 0) {
			return -1;
		}


		comma = q_memchr(_s->s, ',', _s->len);
		if (comma) {


			_s->len -= comma - _s->s + 1;
			_s->s = comma + 1;
			trim_leading(_s);
		}
	} while(comma);


	if (_c->qop.qop_str.s != 0) {
		parse_qop(&_c->qop);
	}


	if (_c->alg.alg_str.s != 0) {
		parse_algorithm(&_c->alg);
	}

	if (_c->username.whole.s != 0) {
		parse_username(&_c->username);
	}

	return 0;
}
