qh_addpoint (pointT *furthest, facetT *facet, boolT checkdist) {
  int goodvisible, goodhorizon;
  vertexT *vertex;
  facetT *newfacet;
  realT dist, newbalance, pbalance;
  boolT isoutside= False;
  int numpart, numpoints;

  if (qh_pointid (furthest) == -1)
    qh_setappend (&qh other_points, furthest);
  if (checkdist || !facet) {
    if (!facet)
      facet= qh facet_list;
    facet= qh_findbest (furthest, facet, False, 0, &dist, &isoutside, &numpart);
    zzadd_(Zpartition, numpart);
    if (!isoutside) {
      zinc_(Znotmax);
      qh_partitioncoplanar (furthest, facet, &dist);
      return True;
    }
  }
  qh_buildtracing (furthest, facet);
  if (qh STOPpoint < 0 && qh furthest_id == -qh STOPpoint-1)
    return False;
  qh_findhorizon (furthest, facet, &goodvisible, &goodhorizon);
  if (qh ONLYgood && !(goodvisible+goodhorizon)) {
    zinc_(Znotgood);


    qh_clearvisible ();
    return True;
  }
  zzinc_(Zprocessed);
  vertex= qh_makenewfacets (furthest );
  newbalance= qh facet_id - qh newfacet_id;
  newbalance -= (realT) (qh num_facets-qh num_visible)*qh hull_dim/qh num_vertices;
  wadd_(Wnewbalance, newbalance);
  wadd_(Wnewbalance2, newbalance * newbalance);
  if (qh ONLYgood && !qh_findgood (qh newfacet_list, goodhorizon)) {
    FORALLnew_facets
      qh_delfacet (newfacet);
    qh_delvertex (vertex);
    qh_clearvisible ();
    qh_clearnewvertices ();
    zinc_(Znotgoodnew);
    return True;
  }
  qh_attachnewfacets();
  qh_matchnewfacets();
  if (qh STOPcone && qh furthest_id == qh STOPcone-1)
    return False;
  if (qh PREmerge)
    qh_merge_nonconvex();
  qh_partitionvisible ( (boolT)!qh_ALL, &numpoints);
  zinc_(Zpbalance);
  pbalance= numpoints - (realT) qh hull_dim
                * (qh num_points - qh num_vertices)/qh num_vertices;
  wadd_(Wpbalance, pbalance);
  wadd_(Wpbalance2, pbalance * pbalance);
  qh_deletevisible ();
  qh_clearnewvertices ();


  if (qh CHECKfrequently) {
    if (qh num_facets < 50)
      qh_checkpolygon (qh facet_list);
    else
      qh_checkpolygon (qh newfacet_list);
  }
  if (qh STOPpoint > 0 && qh furthest_id == qh STOPpoint-1)
    return False;
  trace2((qh ferr, "qh_addpoint: added p%d new facets %d new balance %2.2g point balance %2.2g\n",
    qh_pointid (furthest), qh facet_id - qh newfacet_id, newbalance, pbalance));
  qh newfacet_id= qh facet_id;
  qh newfacet_list= NULL;
  return True;
}
