lexer_init_r(const char * buf, int size) {
  static const char boms[] = { 0xFF, 0xFE, 0, 0, 0xFE, 0xFF },
		    bom_utf8[] = { 0xEF, 0xBB, 0xBF };
  struct lexer * lexer = calloc (1, sizeof (*lexer));

  lexer->lexbuf      = buf;
  lexer->lexbuf_size = size;

  if (size >= 4 && !memcmp (buf, boms + 2, 4))
    lex_convert (lexer, buf + 4, size - 4, UTF32BE);
  else if (size >= 4 && !memcmp (buf, boms, 4))
    lex_convert (lexer, buf + 4, size - 4, UTF32LE);
  else if (size >= 3 && !memcmp (buf, bom_utf8, 3))
  {
    lexer->lexbuf += 3;
    lexer->lexbuf_size -= 3;
  }
  else if (size >= 2 && !memcmp (buf, boms + 4, 2))
    lex_convert (lexer, buf + 2, size - 2, UTF16BE);
  else if (size >= 2 && !memcmp (buf, boms, 2))
    lex_convert (lexer, buf + 2, size - 2, UTF16LE);

  lexer->lexbuf_pos  = 0;
  lexer->lex_mode    = NORMAL;
  lexer->in_comment  = 0;

  lprintf("buffer length %d\n", size);
  return lexer;
}
