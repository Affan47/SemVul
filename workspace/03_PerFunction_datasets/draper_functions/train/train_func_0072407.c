process_command(byte *buf)
{
  int retval = 0;
  ETERM *pattern, *tuple, *cmd, *port, *data;
  pattern = erl_format("{Cmd, Port, Data}");
  tuple = erl_decode(buf);
  if (erl_match(pattern, tuple))
    {
      cmd = erl_var_content(pattern, "Cmd");
      port = erl_var_content(pattern, "Port");
      data = erl_var_content(pattern, "Data");
      switch (ERL_INT_VALUE(cmd))
	{
	case CMD_AUTH:
	  retval = process_auth(port, data);
	  break;
	case CMD_ACCT:
	  retval = process_acct(port, data);
	  break;
	};
      erl_free_term(cmd);
      erl_free_term(port);
      erl_free_term(data);
    }
  erl_free_term(pattern);
  erl_free_term(tuple);
  return retval;
}
