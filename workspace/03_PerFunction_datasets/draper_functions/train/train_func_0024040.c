gfs_source_tension_generic_stability (GfsSourceGeneric * s,
						     GfsSimulation * sim)
{
  GfsSourceTensionGeneric * t = GFS_SOURCE_TENSION_GENERIC (s);
  gdouble h;
  StabilityParams p = { G_MAXDOUBLE, -G_MAXDOUBLE, 0 };

  p.alpha = sim->physical_params.alpha;
  p.c = t->c;
  p.t = t;
  p.sigma = 0.;
  gfs_catch_floating_point_exceptions ();
  gfs_domain_cell_traverse (GFS_DOMAIN (sim), FTT_PRE_ORDER, FTT_TRAVERSE_LEAFS, -1,
			    (FttCellTraverseFunc) min_max_alpha, &p);
  if (gfs_restore_floating_point_exceptions ()) {
    gchar * c = g_strconcat ("\n", gfs_function_description (t->sigma, FALSE), NULL);
    if (p.alpha)
      c = g_strconcat (c, "\n", gfs_function_description (p.alpha, FALSE), NULL);

    g_message ("floating-point exception in user-defined function(s):%s", c);
    exit (1);
  }
  if (p.sigma == 0.)
    return G_MAXDOUBLE;
  h = ftt_level_size (p.depth);
  if (p.alpha) {
    gdouble rhom = (1./p.amin + 1./p.amax)/2.;
    return sqrt (rhom*h*h*h/(M_PI*p.sigma));
  }
  else
    return sqrt (h*h*h/(M_PI*p.sigma));
}
