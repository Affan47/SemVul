sec_asn1d_parse_bit_string (sec_asn1d_state *state,
			    const char *buf, unsigned long len)
{
    unsigned char byte;


    PORT_Assert (state->place == beforeBitString);

    if (state->pending == 0) {
	if (state->dest != NULL) {
	    SECItem *item = (SECItem *)(state->dest);
	    item->data = NULL;
	    item->len = 0;
	    state->place = beforeEndOfContents;
	    return 0;
	}
    }

    if (len == 0) {
	state->top->status = needBytes;
	return 0;
    }

    byte = (unsigned char) *buf;
    if (byte > 7) {
	PORT_SetError (SEC_ERROR_BAD_DER);
	state->top->status = decodeError;
	return 0;
    }

    state->bit_string_unused_bits = byte;
    state->place = duringBitString;
    state->pending -= 1;

    return 1;
}
