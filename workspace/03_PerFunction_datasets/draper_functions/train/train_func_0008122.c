Scan_Quoted_Char(StmInf *pstm, Bool convert, int c0, Bool no_escape)
{
  int radix;
  char *p, *f;
  int x, i;

  Read_Next_Char(pstm, convert);
  if (c == c0)
    {
      if (Scan_Peek_Char(pstm, convert) != c0)
	return -1;

      Read_Next_Char(pstm, convert);
      return c;
    }

  if (c == EOF || c == '\n')
    return -2;

  if (c != '\\' || no_escape)
    return c;

  Read_Next_Char(pstm, convert);
  if (c == '\n')
    return -3;

  if (strchr("\\'\"`", c))
    return c;

  if ((p = (char *) strchr(escape_symbol, c)))
    return escape_char[p - escape_symbol];

  if (c == 'x' || ('0' <= c && c <= '7'))
    {
      if (c == 'x')
	{
	  radix = 16;
	  f = "0123456789abcdefABCDEF";
	  x = 0;
	}
      else
	{
	  radix = 8;
	  f = "01234567";
	  x = c - '0';
	}

      Read_Next_Char(pstm, convert);
      while ((p = strchr(f, c)) != NULL)
	{
	  i = p - f;
	  if (i >= 16)
	    i -= 6;
	  x = x * radix + i;
	  Read_Next_Char(pstm, convert);
	}

      if (!Is_Valid_Code(x) && err_msg == NULL)
	{
	  token.line = pstm->line_count + 1;
	  token.col = pstm->line_pos;
	  err_msg = "invalid character code in \\constant\\ sequence";
	}
      if (c != '\\')
	{
	  if (err_msg == NULL)
	    {
	      token.line = pstm->line_count + 1;
	      token.col = pstm->line_pos;
	      err_msg = "\\ expected in \\constant\\ sequence";
	    }

	  Unget_Last_Char;
	}

      return (int) (unsigned char) x;
    }

  if (err_msg == NULL)
    {
      token.line = pstm->line_count + 1;
      token.col = pstm->line_pos;
      err_msg = "unknown escape sequence";
    }

  return 0;
}
