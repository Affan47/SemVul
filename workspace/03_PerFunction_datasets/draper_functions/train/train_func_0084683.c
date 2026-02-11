parse_framing(hdrcache_t hdrs, struct body_t *body, const char **errstr)
{
    static unsigned max_msgsize = 0;
    const char **hdr;

    if (!max_msgsize) {
	max_msgsize = config_getint(IMAPOPT_MAXMESSAGESIZE);


	if (!max_msgsize) max_msgsize = INT_MAX;
    }

    body->framing = FRAMING_LENGTH;
    body->te = TE_NONE;
    body->len = 0;
    body->max = max_msgsize;


    if ((hdr = spool_getheader(hdrs, "Transfer-Encoding"))) {
	for (; *hdr; hdr++) {
	    tok_t tok = TOK_INITIALIZER(*hdr, ",", TOK_TRIMLEFT|TOK_TRIMRIGHT);
	    char *token;

	    while ((token = tok_next(&tok))) {
		if (body->te & TE_CHUNKED) {

		    break;
		}
		else if (!strcasecmp(token, "chunked")) {
		    body->te |= TE_CHUNKED;
		    body->framing = FRAMING_CHUNKED;
		}
		else if (body->te & ~TE_CHUNKED) {

		    break;
		}
#ifdef HAVE_ZLIB
		else if (!strcasecmp(token, "deflate"))
		    body->te = TE_DEFLATE;
		else if (!strcasecmp(token, "gzip") ||
			 !strcasecmp(token, "x-gzip"))
		    body->te = TE_GZIP;
#endif
		else if (!(body->flags & BODY_DISCARD)) {

		    break;
		}
	    }
	    tok_fini(&tok);
	    if (token) break;
	}

	if (*hdr) {
	    *errstr = "Specified Transfer-Encoding not implemented";
	    return HTTP_NOT_IMPLEMENTED;
	}


	else if (!(body->te & TE_CHUNKED)) {
	    if ((body->flags & BODY_RESPONSE) && (body->flags & BODY_CLOSE)) {
		body->framing = FRAMING_CLOSE;
	    }
	    else {
		*errstr = "Final Transfer-Encoding MUST be \"chunked\"";
		return HTTP_NOT_IMPLEMENTED;
	    }
	}
    }


    else if ((hdr = spool_getheader(hdrs, "Content-Length"))) {
	if (hdr[1]) {
	    *errstr = "Multiple Content-Length header fields";
	    return HTTP_BAD_REQUEST;
	}

	body->len = strtoul(hdr[0], NULL, 10);
	if (body->len > max_msgsize) return HTTP_TOO_LARGE;

	body->framing = FRAMING_LENGTH;
    }


    else if (body->flags & BODY_RESPONSE) {
	if (body->flags & BODY_CLOSE) body->framing = FRAMING_CLOSE;
	else return HTTP_LENGTH_REQUIRED;
    }

    return 0;
}
