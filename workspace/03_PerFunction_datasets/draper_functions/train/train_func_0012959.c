node_is_linked (GtsGNode * n1, GtsGNode * n2, FttDirection d)
{
  GSList * i = GTS_SLIST_CONTAINER (n1)->items;
  while (i) {
    if (GTS_GNODE_NEIGHBOR (n1, i->data) == n2 &&
	GFS_GEDGE (i->data)->d == d)
      return i->data;
    i = i->next;
  }
  return NULL;
}
