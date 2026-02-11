cram_byte_array_stop_decode_init(char *data, int size,
					     enum cram_external_type option,
					     int version) {
    cram_codec *c;
    unsigned char *cp = (unsigned char *)data;

    if (!(c = malloc(sizeof(*c))))
	return NULL;

    c->codec  = E_BYTE_ARRAY_STOP;
    c->decode = (option == E_BYTE_ARRAY_BLOCK)
	? cram_byte_array_stop_decode_block
	: cram_byte_array_stop_decode_char;
    c->free   = cram_byte_array_stop_decode_free;

    c->byte_array_stop.stop = *cp++;
    if (version == CRAM_1_VERS) {
	c->byte_array_stop.content_id = cp[0] + (cp[1]<<8) + (cp[2]<<16)
	    + (cp[3]<<24);
	cp += 4;
    } else {
	cp += itf8_get(cp, &c->byte_array_stop.content_id);
    }

    if ((char *)cp - data != size) {
	fprintf(stderr, "Malformed byte_array_stop header stream\n");
	free(c);
	return NULL;
    }

    return c;
}
