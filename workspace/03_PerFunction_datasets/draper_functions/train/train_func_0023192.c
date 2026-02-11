collapseup(p)
thisperson *p;
{
  thisperson *q, *child, *nextchild;
  boolean down;

  depth++;
  if (depth > (DEPTH_MULTIPLE * numind)) {
    printf("The next pedigree appears to have an unbroken loop\n");
    printf("If you do not think so, increase DEPTH_MULTIPLE in unknown.c\n");
    exit(EXIT_FAILURE);
  }
  p->done = TRUE;
  if (p->foff == NULL) {
    depth--;
    return;
  }
  down = FALSE;
  child = p->foff;
  while (child != NULL) {
    down = FALSE;
    if (p->male)
      q = child->ma;
    else
      q = child->pa;
    if (!q->done) {
      collapsedown(q);
      nextchild = child;
      while (nextchild != NULL) {
	if (nextchild->pa == q || nextchild->ma == q) {
	  if (!nextchild->up)
	    collapseup(nextchild);
	  else
	    down = TRUE;
	}
	if (p->male)
	  nextchild = nextchild->nextpa;
	else
	  nextchild = nextchild->nextma;
      }
      if (q->multi)
	collapseup(q);
      if (!down)
	seg(&p, &q, &child, peelup);
      else
	collapsedown(p);
    }
    if (p->male)
      child = child->nextpa;
    else
      child = child->nextma;
  }
  depth--;
}
