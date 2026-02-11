prot_freex_notip(long nonodes, pointarray treenode)
{

  long i, j;
  node *p;

  for (i = spp; i < nonodes; i++) {
    p = treenode[i];
    do {
      for (j = 0; j < endsite; j++){
        free(p->protx[j]);
        p->protx[j] = NULL;
      }
      free(p->underflows);
      p->underflows = NULL;
      free(p->protx);
      p->protx = NULL;
      p = p->next;
    } while (p != treenode[i]);
  }
}
