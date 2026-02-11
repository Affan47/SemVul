base32_tobuffer(isc_lex_t *lexer, const char base[], isc_boolean_t pad,
		isc_buffer_t *target, int length)
{
	base32_decode_ctx_t ctx;
	isc_textregion_t *tr;
	isc_token_t token;
	isc_boolean_t eol;

	base32_decode_init(&ctx, length, base, pad, target);

	while (!ctx.seen_end && (ctx.length != 0)) {
		unsigned int i;

		if (length > 0)
			eol = ISC_FALSE;
		else
			eol = ISC_TRUE;
		RETERR(isc_lex_getmastertoken(lexer, &token,
					      isc_tokentype_string, eol));
		if (token.type != isc_tokentype_string)
			break;
		tr = &token.value.as_textregion;
		for (i = 0; i < tr->length; i++)
			RETERR(base32_decode_char(&ctx, tr->base[i]));
	}
	if (ctx.length < 0 && !ctx.seen_end)
		isc_lex_ungettoken(lexer, &token);
	RETERR(base32_decode_finish(&ctx));
	return (ISC_R_SUCCESS);
}
