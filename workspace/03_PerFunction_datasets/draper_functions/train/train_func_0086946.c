wsnode_remove (struct wordsplit *wsp, struct wordsplit_node *node)
{
  struct wordsplit_node *p;

  p = node->prev;
  if (p)
    {
      p->next = node->next;
      if (!node->next)
	p->flags &= ~_WSNF_JOIN;
    }
  else
    wsp->ws_head = node->next;

  p = node->next;
  if (p)
    p->prev = node->prev;
  else
    wsp->ws_tail = node->prev;

  node->next = node->prev = NULL;
}
