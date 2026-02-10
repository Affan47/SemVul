automap_edges_mindist(void)
{
  edgelist *p;
  for(p = all_edges; p; p=p->next) {
    int len = p->node->is_oneway ? 4 : 2;
    p->node->min_length = p->node->guess_length = len;
  }
}
