Scan_Next_Number(StmInf *pstm, Bool integer_only)
{
  Bool minus_op = FALSE;

  for (;;)
    {
      Read_Next_Char(pstm, TRUE);
      if (c_type != LA)
	break;
    }


  token.line = pstm->line_count + 1;
  token.col = pstm->line_pos;


  if (c == '-' && isdigit(Scan_Peek_Char(pstm, FALSE)))
    {
      Read_Next_Char(pstm, TRUE);
      minus_op = TRUE;
    }

  if (c_type != DI)
    {
      Unget_Last_Char;
      return "cannot start a number";
    }


  Scan_Number(pstm, integer_only);

  if (minus_op)
    {
      if (token.type == TOKEN_INTEGER)
	token.int_num = -token.int_num;
      else
	token.float_num = -token.float_num;
    }

  return NULL;
}
