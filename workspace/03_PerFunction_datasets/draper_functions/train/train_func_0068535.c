write_euc(charset_spec const *charset, long int input_chr,
		     charset_state *state,
		     void (*emit)(void *ctx, long int output), void *emitctx)
{
    struct euc const *euc = (struct euc *)charset->data;
    unsigned long c;
    int cset, len;

    UNUSEDARG(state);

    if (input_chr == -1)
	return TRUE;


    if (input_chr < 0x80) {
	emit(emitctx, input_chr);
	return TRUE;
    }

    c = euc->from_ucs(input_chr);
    if (!c) {
	return FALSE;
    }

    cset = c >> 28;
    len = euc->nchars[cset-1];
    c &= 0xFFFFFF;

    if (cset > 1)
	emit(emitctx, 0x8C + cset);

    while (len--)
	emit(emitctx, (c >> (8*len)) & 0xFF);
    return TRUE;
}
