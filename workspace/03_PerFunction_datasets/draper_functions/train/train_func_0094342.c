freetree(long nonodes, pointarray treenode)
{

  long i;
  node *p, *q;

  for (i = 0; i < spp; i++)
    free(treenode[i]);
  for (i = spp; i < nonodes; i++) {
    if (treenode[i] != NULL) {
      p = treenode[i]->next;
      do {
        q = p->next;
        free(p);
        p = q;
      } while (p != treenode[i]);
      free(p);
    }
  }
  free(treenode);
}
