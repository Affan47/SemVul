wordsplit_free_nodes (struct wordsplit *wsp)
{
  struct wordsplit_node *p;

  for (p = wsp->ws_head; p;)
    {
      struct wordsplit_node *next = p->next;
      wsnode_free (p);
      p = next;
    }
  wsp->ws_head = wsp->ws_tail = NULL;
}
