hide_outEdge (gint i, PluginInstance *inst)
{
  gint k, edgeid, b;
  graphactd *ga = graphactFromInst (inst);
  GGobiData *d = ga->d;
  GGobiData *e = ga->e;
  ggobid *gg = inst->gg;
  gint nd = g_slist_length (gg->d);
  endpointsd *endpoints;

  if (e == NULL) {
    quick_message ("You haven't designated a set of edges.", false);
return;
  }
  endpoints = resolveEdgePoints(e, d);
  if (endpoints == NULL) {
    g_printerr ("failed to resolve edges. d: %s, e: %s\n", d->name, e->name);
return;
  }

  for (k=0; k<ga->outEdges[i].nels; k++) {
    edgeid = ga->outEdges[i].els[k];
    b = endpoints[edgeid].b;

    e->hidden_now.els[edgeid] = e->hidden.els[edgeid] = true;
    d->hidden_now.els[i] = d->hidden.els[i] = true;

    if (!gg->linkby_cv && nd > 1)
      symbol_link_by_id (true, i, d, gg);


  }
}
