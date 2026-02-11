fprint_btm_mem(FILE *fp, BOOL heading)
{
  int n;
  if (heading)
    fprintf(fp, "  type (bytes each)        gets      frees     in use      bytes\n");

  n = sizeof(struct ac_match_pos);
  fprintf(fp, "ac_match_pos (%4d)%11u%11u%11u%9.1f K\n",
          n, Ac_match_pos_gets, Ac_match_pos_frees,
          Ac_match_pos_gets - Ac_match_pos_frees,
          ((Ac_match_pos_gets - Ac_match_pos_frees) * n) / 1024.);

  n = sizeof(struct ac_match_free_vars_pos);
  fprintf(fp, "ac_match_free_vars_pos (%4d)\n                    %11u%11u%11u%9.1f K\n",
          n, Ac_match_free_vars_pos_gets, Ac_match_free_vars_pos_frees,
          Ac_match_free_vars_pos_gets - Ac_match_free_vars_pos_frees,
          ((Ac_match_free_vars_pos_gets - Ac_match_free_vars_pos_frees) * n) / 1024.);

  n = sizeof(struct btm_state);
  fprintf(fp, "btm_state (%4d)    %11u%11u%11u%9.1f K\n",
          n, Btm_state_gets, Btm_state_frees,
          Btm_state_gets - Btm_state_frees,
          ((Btm_state_gets - Btm_state_frees) * n) / 1024.);

}
