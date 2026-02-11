update_modem_bits(enum ast_fax_modems *bits, const char *value)
{
	char *m[5], *tok, *v = (char *)value;
	int i = 0, j;

	if (!strchr(v, ',')) {
		m[i++] = v;
		m[i] = NULL;
	} else {
		tok = strtok(v, ", ");
		while (tok && (i < 5)) {
			m[i++] = tok;
			tok = strtok(NULL, ", ");
		}
		m[i] = NULL;
	}

	*bits = 0;
	for (j = 0; j < i; j++) {
		if (!strcasecmp(m[j], "v17")) {
			*bits |= AST_FAX_MODEM_V17;
		} else if (!strcasecmp(m[j], "v27")) {
			*bits |= AST_FAX_MODEM_V27;
		} else if (!strcasecmp(m[j], "v29")) {
			*bits |= AST_FAX_MODEM_V29;
		} else if (!strcasecmp(m[j], "v34")) {
			*bits |= AST_FAX_MODEM_V34;
		} else {
			ast_log(LOG_WARNING, "ignoring invalid modem setting: '%s', valid options {v17 | v27 | v29 | v34}\n", m[j]);
		}
	}
	return 0;
}
