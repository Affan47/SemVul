parse_dotoken(std::ostream* os, Token<> tok)
{
	switch (tok.type)
	{

	case token_eof:
		recorderror("Unexpected end of file");
		break;


	case token_comment:
	case token_joinline:
		break;

	case token_whitespace:
	case token_text:
	case token_escape:
		if (os) *os << tok.value;
		break;

	case token_id:
		{
			std::string val;
			if (!symbols.get(tok.value, val))
				if (os) *os << val;
		}
		break;

	case token_if:
		parse_if(os);
		break;

	case token_foreach:
		parse_foreach(os);
		break;

	case token_while:
		parse_while(os);
		break;

	case token_include:
		parse_include(os);
		break;

	case token_includetext:
		parse_includetext(os);
		break;
	case token_using:
		parse_using();
		break;

	case token_set:
		parse_set();
		break;
	case token_setif:
		parse_setif();
		break;
	case token_unset:
		parse_unset();
		break;
	case token_keys:
		parse_keys();
		break;
	case token_push:
		parse_push();
		break;
	case token_pop:
		parse_pop();
		break;

	case token_macro:
		parse_macro();
		break;

	case token_rand:
		tok = parse_rand();
		if (os) *os << tok.value;
		break;

	case token_empty:
		tok = parse_empty();
		if (os) *os << tok.value;
		break;

	case token_size:
		tok = parse_size();
		if (os) *os << tok.value;
		break;

	case token_compare:
		tok = parse_compare();
		if (os) *os << tok.value;
		break;

	case token_isarray:
		tok = parse_isarray();
		if (os) *os << tok.value;
		break;

	case token_ishash:
		tok = parse_ishash();
		if (os) *os << tok.value;
		break;

	case token_isscalar:
		tok = parse_isscalar();
		if (os) *os << tok.value;
		break;

	case token_usermacro:
		if (isuserfunc(tok.value))
			userfunc(tok.value, os);
		else
			user_macro(tok.value, os);
		break;
	case token_next:
		if (looplevel > 0)
			loop_cmd = loop_next;
		else
			recorderror("Syntax error", &tok);
		break;
	case token_last:
		if (looplevel > 0)
			loop_cmd = loop_last;
		else
			recorderror("Syntax error", &tok);
		break;

	default:
		recorderror("Syntax error", &tok);
		break;
	}
}
