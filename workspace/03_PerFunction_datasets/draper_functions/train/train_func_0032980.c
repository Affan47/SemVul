gfs_residual (GfsDomain * domain,
		   guint d,
		   FttTraverseFlags flags,
		   gint max_depth,
		   GfsVariable * u, GfsVariable * rhs, GfsVariable * dia,
		   GfsVariable * res)
{
  RelaxParams p;

  g_return_if_fail (domain != NULL);
  g_return_if_fail (d > 1 && d <= 3);
  g_return_if_fail (u != NULL);
  g_return_if_fail (rhs != NULL);
  g_return_if_fail (dia != NULL);
  g_return_if_fail (res != NULL);

  p.u = u->i;
  p.rhs = rhs->i;
  p.dia = dia->i;
  p.res = res->i;
  p.maxlevel = max_depth;
  gfs_domain_cell_traverse (domain, FTT_PRE_ORDER, flags, max_depth,
			    (FttCellTraverseFunc) (u->centered ?
						   (d == 2 ? residual_set2D : residual_set) :
						   residual_set_dirichlet),
			    &p);
}
