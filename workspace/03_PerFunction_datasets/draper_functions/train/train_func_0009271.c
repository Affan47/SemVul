allocview(tree *a, long nonodes, long totalleles)
{


  long i, j;
  node *p;

  for (i = 0; i < spp; i++)
    a->nodep[i]->view = (phenotype3)Malloc(totalleles*sizeof(double));
  for (i = spp; i < nonodes; i++) {
    p = a->nodep[i];
    for (j = 1; j <= 3; j++) {
      p->view = (phenotype3)Malloc(totalleles*sizeof(double));
      p = p->next;
    }
  }
}
