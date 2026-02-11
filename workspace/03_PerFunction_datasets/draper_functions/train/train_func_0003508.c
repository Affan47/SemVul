gen_excl_set (rtx def)
{
  decl_t decl;
  char **first_str_cpu_units;
  char **second_str_cpu_units;
  int first_vect_length;
  int length;
  int i;

  first_str_cpu_units
    = get_str_vect ((char *) XSTR (def, 0), &first_vect_length, ',', FALSE);
  if (first_str_cpu_units == NULL)
    fatal ("invalid first string `%s' in exclusion_set", XSTR (def, 0));
  second_str_cpu_units = get_str_vect ((char *) XSTR (def, 1), &length, ',',
				       FALSE);
  if (second_str_cpu_units == NULL)
    fatal ("invalid second string `%s' in exclusion_set", XSTR (def, 1));
  length += first_vect_length;
  decl = create_node (sizeof (struct decl) + (length - 1) * sizeof (char *));
  decl->mode = dm_excl;
  decl->pos = 0;
  DECL_EXCL (decl)->all_names_num = length;
  DECL_EXCL (decl)->first_list_length = first_vect_length;
  for (i = 0; i < length; i++)
    if (i < first_vect_length)
      DECL_EXCL (decl)->names [i] = first_str_cpu_units [i];
    else
      DECL_EXCL (decl)->names [i]
	= second_str_cpu_units [i - first_vect_length];
  VLA_PTR_ADD (decls, decl);
  num_dfa_decls++;
}
