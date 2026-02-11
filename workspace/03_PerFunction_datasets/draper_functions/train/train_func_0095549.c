read_cp949(charset_spec const *charset, long int input_chr,
		       charset_state *state,
		       void (*emit)(void *ctx, long int output), void *emitctx)
{
    UNUSEDARG(charset);


    if (state->s0 == 0) {
	if (input_chr >= 0x81 && input_chr <= 0xFE) {


	    state->s0 = input_chr;
	} else {


	    emit(emitctx, input_chr);
	}
    } else {


	if ((input_chr >= 0x40 && input_chr <= 0xFF)) {
	    emit(emitctx, cp949_to_unicode(state->s0 - 0x80,
					   input_chr - 0x40));
	} else {
	    emit(emitctx, ERROR);
	}
	state->s0 = 0;
    }
}
