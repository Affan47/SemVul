asm_id_opcode_lookup (gchar * op_name, gchar * arg1, gchar * arg2)
{
  int i;

  g_assert (op_name);


  for (i = 0; i < sizeof (id_opcode) / sizeof (id_opcode[0]); i++)
	{
	  if (g_ascii_strcasecmp (op_name, id_opcode[i].op_str))
		continue;

	  if (arg1 && g_ascii_strcasecmp (arg1, id_opcode[i].arg1))
		continue;

	  if (arg2 && g_ascii_strcasecmp (arg2, id_opcode[i].arg2))
		continue;

	  return &id_opcode[i];
	}

  return NULL;
}
