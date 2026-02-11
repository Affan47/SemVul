skip_to (int after_equal, char *cmdline)
{

  while (*cmdline && *cmdline != ' ' && *cmdline != '\t' &&
	 ! (after_equal && *cmdline == '='))
    cmdline ++;


  while (*cmdline == ' ' || *cmdline == '\t' ||
	 (after_equal && *cmdline == '='))
    cmdline ++;

  return cmdline;
}
