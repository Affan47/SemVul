assign_random_edge_color(Agraph_t* g){
  char cstring[8];
  char buf2[1024];
  Agsym_t *sym2;
  Agnode_t* n;
  Agedge_t *ep;

  sym2 = agattr(g, AGEDGE, "color", "");
  for (n = agfstnode (g); n; n = agnxtnode (g, n)) {
    for (ep = agfstedge(g, n); ep; ep = agnxtedge(g, ep, n)) {
      sprintf (buf2, "%s", hue2rgb(0.65*drand(), cstring));
      agxset (ep, sym2, buf2);
    }
  }

  return g;
 }
