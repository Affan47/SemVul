pdf_lex(fz_stream *f, pdf_lexbuf *buf)
{
	while (1)
	{
		int c = fz_read_byte(f);
		switch (c)
		{
		case EOF:
			return PDF_TOK_EOF;
		case IS_WHITE:
			lex_white(f);
			break;
		case '%':
			lex_comment(f);
			break;
		case '/':
			lex_name(f, buf);
			return PDF_TOK_NAME;
		case '(':
			return lex_string(f, buf);
		case ')':
			fz_warn(f->ctx, "lexical error (unexpected ')')");
			continue;
		case '<':
			c = fz_read_byte(f);
			if (c == '<')
			{
				return PDF_TOK_OPEN_DICT;
			}
			else
			{
				fz_unread_byte(f);
				return lex_hex_string(f, buf);
			}
		case '>':
			c = fz_read_byte(f);
			if (c == '>')
			{
				return PDF_TOK_CLOSE_DICT;
			}
			fz_warn(f->ctx, "lexical error (unexpected '>')");
			continue;
		case '[':
			return PDF_TOK_OPEN_ARRAY;
		case ']':
			return PDF_TOK_CLOSE_ARRAY;
		case '{':
			return PDF_TOK_OPEN_BRACE;
		case '}':
			return PDF_TOK_CLOSE_BRACE;
		case IS_NUMBER:
			return lex_number(f, buf, c);
		default:
			fz_unread_byte(f);
			lex_name(f, buf);
			return pdf_token_from_keyword(buf->scratch);
		}
	}
}
