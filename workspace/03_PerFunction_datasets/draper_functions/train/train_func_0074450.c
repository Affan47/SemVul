gap_codegen_gen_tab_iter_ALT(char  *proc_name)
{
  FILE           *l_fp;
  char             l_clean_proc_name[256];

  p_clean_name(proc_name, &l_clean_proc_name[0]);
  l_fp = g_fopen(GEN_TABFILE_NAME, "a");
  if(l_fp != NULL)
  {
    fprintf(l_fp, "   , { \"%s\",  p_%s_iter_ALT }\n",
                  l_clean_proc_name, l_clean_proc_name);
    fclose(l_fp);
  }
  return 0;
}
