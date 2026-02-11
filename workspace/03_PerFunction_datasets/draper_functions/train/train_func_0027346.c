initboolnames(node *p, boolean *names)
{

  node *q;

  if (p->tip) {
    names[p->index - 1] = true;
    return;
  }
  q = p->next;
  while (q != p) {
    initboolnames(q->back, names);
    q = q->next;
  }
}
