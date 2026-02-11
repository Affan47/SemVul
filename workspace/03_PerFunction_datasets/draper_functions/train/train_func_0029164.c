protmakevalues()
{

  long i, j;
  node *p;

  for (i = 1; i <= nonodes; i++) {
    treenode[i - 1]->back = NULL;
    treenode[i - 1]->tip = (i <= spp);
    treenode[i - 1]->index = i;
    for (j = 0; j < (chars); j++)
      treenode[i - 1]->numsteps[j] = 0;
    if (i > spp) {
      p = treenode[i - 1]->next;
      while (p != treenode[i - 1]) {
        p->back = NULL;
        p->tip = false;
        p->index = i;
        for (j = 0; j < (chars); j++)
          p->numsteps[j] = 0;
        p = p->next;
      }
    }
  }
}
