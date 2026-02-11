smooth(node *p)
{
  long i, num_sibs;
  node *sib_ptr;

  smoothed = false;
  update (p);
  if (p->tip)
    return;

  num_sibs = count_sibs (p);
  sib_ptr  = p;

  for (i=0; i < num_sibs; i++) {
    sib_ptr = sib_ptr->next;

    if (polishing || (smoothit && !smoothed)) {
      smooth(sib_ptr->back);
    }
  }
}
