fix_applies (tFixDesc* p_fixd)
{
  const char *pz_fname = pz_curr_file;
  const char *pz_scan = p_fixd->file_list;
  int test_ct;
  tTestDesc *p_test;

# ifdef SEPARATE_FIX_PROC


  if (p_fixd->fd_flags & (FD_SHELL_SCRIPT | FD_SKIP_TEST))
    return BOOL_FALSE;
# else
  if (p_fixd->fd_flags & FD_SKIP_TEST)
    return BOOL_FALSE;
# endif


  if (pz_scan != (char *) NULL)
    {
      size_t name_len;

      while ((pz_fname[0] == '.') && (pz_fname[1] == '/'))
        pz_fname += 2;
      name_len = strlen (pz_fname);

      for (;;)
        {
          pz_scan = strstr (pz_scan + 1, pz_fname);


          if (pz_scan == (char *) NULL)
            return BOOL_FALSE;


          if ((pz_scan[-1] == '|') && (pz_scan[name_len] == '|'))
            break;
        }
    }


  for (p_test = p_fixd->p_test_desc, test_ct = p_fixd->test_ct;
       test_ct-- > 0;
       p_test++)
    {
      switch (p_test->type)
        {
        case TT_TEST:
          if (test_test (p_test, pz_curr_file) != APPLY_FIX) {
#ifdef DEBUG
            if (VLEVEL( VERB_EVERYTHING ))
              fprintf (stderr, z_failed, "TEST", p_fixd->fix_name,
                       pz_fname, p_fixd->test_ct - test_ct);
#endif
            return BOOL_FALSE;
          }
          break;

        case TT_EGREP:
          if (egrep_test (pz_curr_data, p_test) != APPLY_FIX) {
#ifdef DEBUG
            if (VLEVEL( VERB_EVERYTHING ))
              fprintf (stderr, z_failed, "EGREP", p_fixd->fix_name,
                       pz_fname, p_fixd->test_ct - test_ct);
#endif
            return BOOL_FALSE;
          }
          break;

        case TT_NEGREP:
          if (egrep_test (pz_curr_data, p_test) == APPLY_FIX) {
#ifdef DEBUG
            if (VLEVEL( VERB_EVERYTHING ))
              fprintf (stderr, z_failed, "NEGREP", p_fixd->fix_name,
                       pz_fname, p_fixd->test_ct - test_ct);
#endif

            return BOOL_FALSE;
          }
          break;

        case TT_FUNCTION:
          if (run_test (p_test->pz_test_text, pz_curr_file, pz_curr_data)
              != APPLY_FIX) {
#ifdef DEBUG
            if (VLEVEL( VERB_EVERYTHING ))
              fprintf (stderr, z_failed, "FTEST", p_fixd->fix_name,
                       pz_fname, p_fixd->test_ct - test_ct);
#endif
            return BOOL_FALSE;
          }
          break;
        }
    }

  return BOOL_TRUE;
}
