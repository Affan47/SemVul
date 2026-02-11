protsavetree(long *pos, boolean *found)
{


  long i, j;
  node *p;
  boolean done;

  protreroot(treenode[outgrno - 1]);
  protsavetraverse(root, pos,found);
  for (i = 0; i < (nonodes); i++)
    place[i] = 0;
  place[root->index - 1] = 1;
  for (i = 1; i <= (spp); i++) {
    p = treenode[i - 1];
    while (place[p->index - 1] == 0) {
      place[p->index - 1] = i;
      while (!p->bottom)
        p = p->next;
      p = p->back;
    }
    if (i > 1) {
      place[i - 1] = place[p->index - 1];
      j = place[p->index - 1];
      done = false;
      while (!done) {
        place[p->index - 1] = spp + i - 1;
        while (!p->bottom)
          p = p->next;
        p = p->back;
        done = (p == NULL);
        if (!done)
          done = (place[p->index - 1] != j);
      }
    }
  }
}
