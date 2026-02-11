encoding_free (struct encoding * encoding)
{
  int i;

  XFREE (encoding->key);
  XFREE (encoding->name);
  XFREE (encoding->default_font);
  XFREE (encoding->documentation);

  for (i = 0 ; i < 256 ; i++)
    free (encoding->vector [i]);

  pair_table_free (encoding->substitutes);
  da_free (encoding->font_names_used, (da_map_func_t) free);
  font_table_free (encoding->fonts);

  for (i = 0 ; base_faces [i] != -1 ; i++)
    free (encoding->faces_wx [base_faces [i]]);
  free (encoding);
}
