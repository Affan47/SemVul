read_sjis(charset_spec const *charset, long int input_chr,
		      charset_state *state,
		      void (*emit)(void *ctx, long int output), void *emitctx)
{
    UNUSEDARG(charset);


    if (state->s0 == 0) {
	if ((input_chr >= 0x81 && input_chr <= 0x9F) ||
	    (input_chr >= 0xE0 && input_chr <= 0xEF)) {


	    state->s0 = input_chr;
	} else {


	    if (input_chr == 0x5C)
		input_chr = 0xA5;
	    else if (input_chr == 0x7E)
		input_chr = 0x203E;
	    else if (input_chr >= 0xA1 && input_chr <= 0xDF)
		input_chr += 0xFF61 - 0xA1;
	    else if (input_chr < 0x80)
		;
	    else
		input_chr = ERROR;
	    emit(emitctx, input_chr);
	}
    } else {


	if (input_chr >= 0x40 && input_chr <= 0xFC && input_chr != 0x7F) {
	    int r, c;
	    r = state->s0;
	    if (r >= 0xE0) r -= (0xE0 - 0xA0);
	    r -= 0x81;
	    c = input_chr;
	    if (c > 0x7F) c--;
	    c -= 0x40;
	    r *= 2;
	    if (c >= 94)
		r++, c -= 94;
	    emit(emitctx, jisx0208_to_unicode(r, c));
	} else {
	    emit(emitctx, ERROR);
	}
	state->s0 = 0;
    }
}
