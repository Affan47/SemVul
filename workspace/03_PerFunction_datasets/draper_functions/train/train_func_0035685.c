Read_Switch(void)
{
  int k;

  Read_Token('(');
  nb_swt = 0;
  for (;;)
    {
      if (Scanner() != INTEGER)
	Syntax_Error("integer expected");

      Read_Token('=');
      Read_Token(IDENTIFIER);
      swt[nb_swt].int_val = int_val;
      swt[nb_swt].label = strdup(str_val);

      nb_swt++;
      k = Scanner();
      if (k == ')')
	break;
      if (k != ',')
	Syntax_Error(") or , expected");
    }
}
