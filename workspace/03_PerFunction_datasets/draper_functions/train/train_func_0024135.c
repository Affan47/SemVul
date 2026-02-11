gfs_linear_problem_new (GfsDomain * domain)
{
  g_return_val_if_fail (domain != NULL, NULL);

  GfsLinearProblem * lp = g_malloc (sizeof (GfsLinearProblem));

  lp->rhs = g_array_new (FALSE, FALSE, sizeof (gdouble));
  lp->lhs = g_array_new (FALSE, FALSE, sizeof (gdouble));
  lp->LP = g_ptr_array_new ();
  lp->id = gfs_temporary_variable (domain);
  lp->neighbor = gfs_temporary_variable (domain);
  lp->neighborw = gfs_temporary_variable (domain);
  lp->istart = 0;

  return lp;
}
