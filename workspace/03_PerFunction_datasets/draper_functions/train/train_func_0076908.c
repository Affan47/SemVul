init_tsin_table()
{
  char fname[256];
  if (!current_CS)
    return;

  init_tsin_table_fname(&inmd[current_CS->in_method], fname);
  load_tsin_db0(fname, TRUE);
}
