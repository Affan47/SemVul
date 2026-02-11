role_unit_precalcs(void)
{
  int i;

  if (first_init) {
    for (i = 0; i < L_LAST; i++) {
      with_role[i] = NULL;
      n_with_role[i] = 0;
    }
  } else {
    role_unit_precalcs_free();
  }

  for(i=0; i<F_LAST; i++) {
    precalc_one(i, utype_has_flag);
  }
  for(i=L_FIRST; i<L_LAST; i++) {
    precalc_one(i, utype_has_role);
  }
  first_init = FALSE;
}
