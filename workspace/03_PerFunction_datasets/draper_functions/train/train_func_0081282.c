scm_i_get_one_zombie (SCM guardian)
{
  t_guardian *g = GUARDIAN_DATA (guardian);
  SCM res = SCM_BOOL_F;

  if (!TCONC_EMPTYP (g->zombies))
    TCONC_OUT (g->zombies, res);

  return res;
}
