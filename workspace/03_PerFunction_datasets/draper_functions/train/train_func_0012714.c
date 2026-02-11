qh_makenewfacets (pointT *point ) {
  facetT *visible, *newfacet= NULL, *newfacet2= NULL, *neighbor, **neighborp;
  vertexT *apex;
  int numnew=0;

  qh newfacet_list= qh facet_tail;
  qh newvertex_list= qh vertex_tail;
  qh newfacet_id= qh facet_id;
  apex= qh_newvertex(point);
  apex->newlist= True;
  qh_appendvertex (apex);
  qh visit_id++;
  if (!qh ONLYgood)
    qh NEWfacets= True;
  FORALLvisible_facets {
    FOREACHneighbor_(visible)
      neighbor->seen= False;
    if (visible->ridges) {
      visible->visitid= qh visit_id;
      newfacet2= qh_makenew_nonsimplicial (visible, apex, &numnew);
    }
    if (visible->simplicial)
      newfacet= qh_makenew_simplicial (visible, apex, &numnew);
    if (!qh ONLYgood) {
      if (newfacet2)
        newfacet= newfacet2;
      if (!newfacet)
        zinc_(Zinsidevisible);
      SETfirst_(visible->neighbors)= newfacet;
      SETsecond_(visible->neighbors)= NULL;
    }
  }
  trace1((qh ferr, "qh_makenewfacets: created %d new facets from point p%d to horizon\n",
	  numnew, qh_pointid(point)));


  return apex;
}
