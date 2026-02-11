qh_flippedmerges(facetT *facetlist) {
  facetT *facet, *neighbor, *facet1, *facet2;
  realT dist, mindist, maxdist;
  mergeT *merge;
  setT *othermerges= qh_settemp (qh TEMPsize);
  int nummerge=0;

  trace2((qh ferr, "qh_flippedmerges: begin\n"));
  FORALLfacet_(facetlist) {
    if (facet->flipped)
      qh_appendmergeset (facet, facet, NULL);
  }
  while ((merge= (mergeT *)qh_setdellast (qh facet_mergeset))) {
    if (merge->angle >= qh_ANGLEdegen) {
      qh_setappend (&othermerges, merge);
      continue;
    }
    facet1= merge->facet1;
    facet2= merge->facet2;
    qh_memfree (merge, sizeof(mergeT));
    if (facet1->visible || facet2->visible)
      continue;
    if (qh TRACEmerge-1 == zzval_(Ztotmerge))
      qhmem.IStracing= qh IStracing= qh TRACElevel;
    neighbor= qh_findbestneighbor (facet1, &dist, &mindist, &maxdist);
    trace0((qh ferr, "qh_flippedmerges: merge flipped f%d into f%d dist %2.2g\n",
      facet1->id, neighbor->id, dist));
    qh_mergefacet (facet1, neighbor, &mindist, &maxdist, NULL);
    nummerge++;
    if (qh PRINTstatistics) {
      zinc_(Zflipped);
      wadd_(Wflippedtot, dist);
      wmax_(Wflippedmax, dist);
    }
  }
  if (qh_setsize (othermerges)) {
    qh_settemppop();
    qh_settempfree (&qh facet_mergeset);
    qh facet_mergeset= othermerges;
    qh_settemppush (othermerges);
  }else
    qh_settempfree (&othermerges);
  trace1((qh ferr, "qh_flippedmerges: merged %d flipped facets into a good neighbor\n", nummerge));
}
