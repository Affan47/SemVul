splot_hidden_edge (gint m, GGobiData * d, GGobiData * e,
                   splotd * sp, displayd * display, ggobid * gg)
{
  gint a, b;
  gboolean hiddenp = false;
  endpointsd *endpoints;

  endpoints = resolveEdgePoints (e, d);
  if (endpoints && edge_endpoints_get (m, &a, &b, d, endpoints, e))
    if (e->hidden_now.els[m] || d->hidden_now.els[a] || d->hidden_now.els[b])
      hiddenp = true;


  return hiddenp;
}
