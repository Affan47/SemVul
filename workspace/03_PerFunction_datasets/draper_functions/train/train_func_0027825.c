cram_external_decode_init(char *data, int size,
				      enum cram_external_type option,
				      int version) {
    cram_codec *c;
    char *cp = data;

    if (!(c = malloc(sizeof(*c))))
	return NULL;

    c->codec  = E_EXTERNAL;
    if (option == E_INT || option == E_LONG)
	c->decode = cram_external_decode_int;
    else if (option == E_BYTE_ARRAY || option == E_BYTE)
	c->decode = cram_external_decode_char;
    else
	c->decode = cram_external_decode_block;
    c->free   = cram_external_decode_free;

    cp += itf8_get(cp, &c->external.content_id);

    if (cp - data != size) {
	fprintf(stderr, "Malformed external header stream\n");
	free(c);
	return NULL;
    }

    c->external.type = option;

    return c;
}
