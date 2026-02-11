setuptree(pointarray treenode, long nonodes, boolean usertree)
{

  long i;
  node *p;

  for (i = 1; i <= nonodes; i++) {
    if (i <= spp || !usertree) {
      treenode[i-1]->back = NULL;
      treenode[i-1]->tip = (i <= spp);
      treenode[i-1]->index = i;
      treenode[i-1]->numdesc = 0;
      treenode[i-1]->iter = true;
      treenode[i-1]->initialized = true;
      treenode[i-1]->tyme =  0.0;
    }
  }
  if (!usertree) {
    for (i = spp + 1; i <= nonodes; i++) {
      p = treenode[i-1]->next;
      while (p != treenode[i-1]) {
        p->back = NULL;
        p->tip = false;
        p->index = i;
        p->numdesc = 0;
        p->iter = true;
        p->initialized = false;
        p->tyme = 0.0;
        p = p->next;
      }
    }
  }
}
