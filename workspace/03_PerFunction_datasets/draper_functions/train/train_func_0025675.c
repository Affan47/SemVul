nodeinit(node *p)
{

  node *sib_ptr, *sib_back_ptr;
  long i, num_sibs;
  double lowertyme;

  sib_ptr = p;
  num_sibs = count_sibs(p);


  lowertyme = p->next->back->tyme;
  for (i=0 ; i < num_sibs; i++) {
    sib_ptr      = sib_ptr->next;
    sib_back_ptr = sib_ptr->back;
    if (sib_back_ptr->tyme < lowertyme)
      lowertyme = sib_back_ptr->tyme;
  }

  p->tyme = lowertyme - 0.1;

  sib_ptr = p;
  for (i=0 ; i < num_sibs; i++) {
    sib_ptr = sib_ptr->next;
    sib_back_ptr = sib_ptr->back;

    sib_ptr->tyme = p->tyme;
    sib_back_ptr->v = sib_back_ptr->tyme - p->tyme;
    sib_ptr->v = sib_back_ptr->v;
  }
}
