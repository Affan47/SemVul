Scan_Quoted(StmInf *pstm)
{
  int c0;
  char *s;
  Bool convert = (c_orig != '\'');
  Bool no_escape;
  int i = 0;

  if (c_type == QT)
    {
      token.type = TOKEN_NAME;
      i = 0;
    }
  else if (c_type == DQ)
    {
      token.type = TOKEN_STRING;
      i = Flag_Value(FLAG_DOUBLE_QUOTES);
    }
  else
    {
      token.type = TOKEN_BACK_QUOTED;
      i = Flag_Value(FLAG_BACK_QUOTES);
    }

  s = token.name;
  c0 = c;
  no_escape = i >> FLAG_NO_ESCAPE_BIT;

  for (;;)
    {
      c = Scan_Quoted_Char(pstm, convert, c0, no_escape);
      if (c == -1)
	{
	  *s = '\0';
	  return;
	}

      if (c == -2)
	break;

      if (c == -3)
	continue;

      *s++ = c;
    }

  *s = '\0';

  if (err_msg)
    return;

  Unget_Last_Char;

  token.line = pstm->line_count + 1;
  token.col = pstm->line_pos + 1;

  switch (token.type)
    {
    case TOKEN_NAME:
      err_msg = "quote character expected here";
      break;

    case TOKEN_BACK_QUOTED:
      err_msg = "back quote character expected here";
      break;

    case TOKEN_STRING:
      err_msg = "double quote character expected here";
      break;

    default:
      ;
    }
}
