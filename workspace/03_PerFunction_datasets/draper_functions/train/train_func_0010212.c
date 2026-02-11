get_string_list_index (SANE_String_Const list[], SANE_String_Const name)
{
  int index;

  index = 0;
  while (list[index] != NULL)
    {
      if (strcmp (list[index], name) == 0)
	{
	  return (index);
	}
      index++;
    }

  DBG (DBG_error, "name %s not found in list\n", name);

  assert (0 == 1);

  return (-1);
}
