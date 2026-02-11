gettoken_color(lexer_token t)
{
	switch (t) {
		case LEX_CTOK_WHITESPACE: return getcolor_syntax(palidx_syntax_whitespace);
		case LEX_CTOK_COMMENT: return getcolor_syntax(palidx_syntax_comment);
		case LEX_CTOK_PREPROCESS: return getcolor_syntax(palidx_syntax_preprocess);
		case LEX_CTOK_IDENTIFIER: return getcolor_syntax(palidx_syntax_identifier);
		case LEX_CTOK_RIDENTIFIER: return getcolor_syntax(palidx_syntax_reserved);
		case LEX_CTOK_NUMBER: return getcolor_syntax(palidx_syntax_intnum);
		case LEX_CTOK_FNUMBER: return getcolor_syntax(palidx_syntax_floatnum);
		case LEX_CTOK_STRING: return getcolor_syntax(palidx_syntax_string);
		case LEX_CTOK_CHAR: return getcolor_syntax(palidx_syntax_char);
		case LEX_CTOK_SYMBOL: return getcolor_syntax(palidx_syntax_symbol);
	}
	return VCP(VC_BLACK, VC_RED);
}
