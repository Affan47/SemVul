asm_util_parse_number (gchar * str, gint * value)
{

  g_assert (str);
  if (!g_ascii_isdigit (str[0]))
	return FALSE;

  if (str[strlen (str) - 1] == 'h' || str[strlen (str) - 1] == 'H')
	{
	  str[strlen (str) - 1] = '\0';

	  return asm_util_str_to_int (str, value, 16);
	}
  if (str[strlen (str) -1] == 'b' || str[strlen (str) - 1] == 'B')
  	{
  	  str[strlen (str) - 1] = '\0';

  	  return asm_util_str_to_int (str,value, 2);
  	}
  if (str[strlen (str) - 1] == 'o' || str[strlen (str) - 1] == 'O')
	{
	  str[strlen (str) - 1] = '\0';

	  return asm_util_str_to_int (str, value, 8);
	}

  return asm_util_str_to_int (str, value, 10);
}
