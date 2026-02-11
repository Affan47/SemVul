qh_getmergeset(facetT *facetlist) {
  facetT *facet, *neighbor, **neighborp;
  ridgeT *ridge, **ridgep;
  int nummerges;

  nummerges= qh_setsize (qh facet_mergeset);
  trace2((qh ferr, "qh_getmergeset: started.\n"));
  FORALLfacet_(facetlist) {
    if (!facet->center) {
      facet->tested= False;
      FOREACHridge_(facet->ridges)
	ridge->tested= False;
    }
    if (facet->tested)
      continue;
    facet->tested= True;
    FOREACHneighbor_(facet)
      neighbor->seen= False;
    FOREACHridge_(facet->ridges) {
      if (ridge->tested && !ridge->nonconvex)
	continue;
      ridge->tested= True;
      ridge->nonconvex= False;
      neighbor= otherfacet_(ridge, facet);
      if (!neighbor->seen) {
	neighbor->seen= True;
	if (qh_test_appendmerge (facet, neighbor))
	  ridge->nonconvex= True;
      }
    }
  }
  nummerges= qh_setsize (qh facet_mergeset);
  qsort(SETaddr_(qh facet_mergeset, mergeT), nummerges,sizeof(mergeT *),qh_compareangle);
  trace2((qh ferr, "qh_getmergeset: %d merges found\n", nummerges));
}
