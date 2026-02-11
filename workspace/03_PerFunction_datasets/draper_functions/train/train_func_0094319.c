savetraverse(node *p)
{

  node *q;

  p->bottom = true;
  if (p->tip)
    return;
  q = p->next;
  while (q != p) {
    q->bottom = false;
    savetraverse(q->back);
    q = q->next;
  }
}
