gen_query_cpu_unit (rtx def)
{
  decl_t decl;
  char **str_cpu_units;
  int vect_length;
  int i;

  str_cpu_units = get_str_vect ((char *) XSTR (def, 0), &vect_length, ',',
				FALSE);
  if (str_cpu_units == NULL)
    fatal ("invalid string `%s' in define_query_cpu_unit", XSTR (def, 0));
  for (i = 0; i < vect_length; i++)
    {
      decl = create_node (sizeof (struct decl));
      decl->mode = dm_unit;
      decl->pos = 0;
      DECL_UNIT (decl)->name = check_name (str_cpu_units [i], decl->pos);
      DECL_UNIT (decl)->automaton_name = (char *) XSTR (def, 1);
      DECL_UNIT (decl)->query_p = 1;
      VLA_PTR_ADD (decls, decl);
      num_dfa_decls++;
    }
}
