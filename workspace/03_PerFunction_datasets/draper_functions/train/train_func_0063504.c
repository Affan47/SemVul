create_espeak_punctuation_list(const wchar_t *punctlist)
{
  ENTER("create_espeak_punctuation_list");
  int a_error=1;

  t_espeak_command* a_command = (t_espeak_command*)malloc(sizeof(t_espeak_command));

  if (!punctlist || !a_command)
    {
      goto list_error;
    }

  a_command->type = ET_PUNCTUATION_LIST;
  a_command->state = CS_UNDEFINED;

  {
    size_t len = (wcslen(punctlist) + 1)*sizeof(wchar_t);
    wchar_t* a_list = (wchar_t*)malloc(len);
    memcpy(a_list, punctlist, len);
    a_command->u.my_punctuation_list = a_list;
  }

  a_error=0;

 list_error:
  if (a_error)
    {
      if (a_command)
	{
	  free (a_command);
	}
      a_command = NULL;
    }

  SHOW("command=0x%x\n", a_command);

  return a_command;
}
