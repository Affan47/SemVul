get_accept_type(const char **hdr, struct mime_type_t *types)
{
    struct mime_type_t *ret = NULL;
    struct accept *e, *enc = parse_accept(hdr);

    for (e = enc; e && e->token; e++) {
	if (!ret && e->qual > 0.0) {
	    struct mime_type_t *m;

	    for (m = types; !ret && m->content_type; m++) {
		if (is_mediatype(e->token, m->content_type)) ret = m;
	    }
	}

	free(e->token);
    }
    if (enc) free(enc);

    return ret;
}
