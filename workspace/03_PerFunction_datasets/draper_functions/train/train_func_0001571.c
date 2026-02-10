gen_bypass (rtx def)
{
  decl_t decl;
  char **out_patterns;
  int out_length;
  char **in_patterns;
  int in_length;
  int i, j;

  out_patterns = get_str_vect (XSTR (def, 1), &out_length, ',', FALSE);
  if (out_patterns == NULL)
    fatal ("invalid string `%s' in define_bypass", XSTR (def, 1));
  in_patterns = get_str_vect (XSTR (def, 2), &in_length, ',', FALSE);
  if (in_patterns == NULL)
    fatal ("invalid string `%s' in define_bypass", XSTR (def, 2));
  for (i = 0; i < out_length; i++)
    for (j = 0; j < in_length; j++)
      {
	decl = XCREATENODE (struct decl);
	decl->mode = dm_bypass;
	decl->pos = 0;
	DECL_BYPASS (decl)->latency = XINT (def, 0);
	DECL_BYPASS (decl)->out_pattern = out_patterns[i];
	DECL_BYPASS (decl)->in_pattern = in_patterns[j];
	DECL_BYPASS (decl)->bypass_guard_name = XSTR (def, 3);
	decls.safe_push (decl);
      }
}
