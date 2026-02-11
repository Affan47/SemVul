output_token(const yystype *token, struct scope *scope, struct buf *out, char lastchar)
{
	char sbuf[128];
	const char *s = TOKEN_GET(token, cstring);

	switch(token->type) {
		case TOK_StringLiteral:
			output_space(lastchar,'"', out);
			buf_outc('"', out);
			if(s) {
				buf_outs(s, out);
			}
			buf_outc('"', out);
			return '\"';
		case TOK_NumericInt:
			output_space(lastchar,'0', out);
			snprintf(sbuf, sizeof(sbuf), "%ld", TOKEN_GET(token, ival));
			buf_outs(sbuf, out);
			return '0';
		case TOK_NumericFloat:
			output_space(lastchar,'0', out);
			snprintf(sbuf, sizeof(sbuf), "%g", TOKEN_GET(token, dval));
			buf_outs(sbuf, out);
			return '0';
		case TOK_IDENTIFIER_NAME:
			output_space(lastchar,'a', out);
			if(s) {
				long id = scope_lookup(scope, s, strlen(s));
				if(id == -1) {

					buf_outs(s, out);
				} else {
					snprintf(sbuf, sizeof(sbuf), "n%03ld",id);
					buf_outs(sbuf, out);
				}
			}
			return 'a';
		case TOK_FUNCTION:
			output_space(lastchar,'a', out);
			buf_outs("function",out);
			return 'a';
		default:
			if(s) {
				const size_t len = strlen(s);
				output_space(lastchar,s[0], out);
				buf_outs(s, out);
				return len ? s[len-1] : '\0';
			}
			return '\0';
	}
}
