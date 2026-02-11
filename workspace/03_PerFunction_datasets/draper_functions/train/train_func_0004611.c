find_command (char *command)
{
  char *ptr;
  char c;
  struct builtin **builtin;


  ptr = command;
  while (*ptr && *ptr != ' ' && *ptr != '\t' && *ptr != '=')
    ptr ++;

  c = *ptr;
  *ptr = 0;


  for (builtin = builtin_table; *builtin != 0; builtin++)
    {
      int ret = grub_strcmp (command, (*builtin)->name);

      if (ret == 0)
	{

	  *ptr = c;
	  return *builtin;
	}
      else if (ret < 0)
	break;
    }


  errnum = ERR_UNRECOGNIZED;
  *ptr = c;
  return 0;
}
