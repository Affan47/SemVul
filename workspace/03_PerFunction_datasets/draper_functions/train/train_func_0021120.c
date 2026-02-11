parseId(YYSTYPE *lvalp, yyscan_t scanner)
{
	const struct keyword *kw;
	const unsigned char *in = (const unsigned char*)scanner->in;
	scanner->state = Initial;
	while(scanner->pos < scanner->insize) {
		unsigned char c = in[scanner->pos++];
		enum char_class cClass = id_ctype[c];
		switch(cClass) {
			case IdStart:
				textbuffer_putc(&scanner->buf, c);
				break;
			case Operator:

				assert(c == '\\');
				if(scanner->pos < scanner->insize &&
						in[scanner->pos++] == 'u') {
					textbuffer_putc(&scanner->buf, c);
					break;
				}
				if(scanner->pos == scanner->insize) {
					scanner->pos++;
				}

			default:

				scanner->state = Initial;
				textbuffer_putc(&scanner->buf, '\0');
				scanner->pos--;
				kw = in_word_set(scanner->buf.data, scanner->buf.pos-1);
				if(kw) {

					TOKEN_SET(lvalp, cstring, kw->name);
					return kw->val;
				}

				TOKEN_SET(lvalp, cstring, NULL);
				return TOK_IDENTIFIER_NAME;
		}
	}
	scanner->state = Identifier;
	return 0;
}
