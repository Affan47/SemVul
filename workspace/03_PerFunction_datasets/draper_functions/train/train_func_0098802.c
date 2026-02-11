skip_name(str* _s)
{
	char* last_wsp, *p;
	int i, quoted = 0;


	if (!_s) {
		LM_ERR("invalid parameter value\n");
		return -1;
	}

	p = _s->s;

	last_wsp = 0;

	for(i = 0; i < _s->len; i++) {
		if (!quoted) {
			if ((*p == ' ') || (*p == '\t')) {
				last_wsp = p;
			} else {
				if (*p == '<') {
					_s->s = p;
					_s->len -= i;
					return 0;
				}

				if (*p == ':') {
					if (last_wsp) {
						_s->s = last_wsp;
						_s->len -= last_wsp - _s->s + 1;
					}
					return 0;
				}

				if (*p == '\"') {
					quoted = 1;
				}
			}
		} else {
			if ((*p == '\"') && (*(p-1) != '\\')) quoted = 0;
		}
		p++;
	}

	if (quoted) {
		LM_ERR("closing quote missing in name part of Contact\n");
	} else {
		LM_ERR("error in contact, scheme separator not found\n");
	}

	return -1;
}
