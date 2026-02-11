qh_prependfacet(facetT *facet, facetT **facetlist) {
  facetT *prevfacet, *list= *facetlist;


  trace4((qh ferr, "qh_prependfacet: prepend f%d before f%d\n",
	  facet->id, list->id));
  prevfacet= list->previous;
  facet->previous= prevfacet;
  if (prevfacet)
    prevfacet->next= facet;
  list->previous= facet;
  facet->next= *facetlist;
  if (qh facet_list == list)
    qh facet_list= facet;
  if (qh facet_next == list)
    qh facet_next= facet;
  *facetlist= facet;
  qh num_facets++;
}
