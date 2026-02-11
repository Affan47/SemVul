savetraverse(node2 *p)
{

  p->bottom = true;
  if (p->tip)
    return;
  p->next->bottom = false;
  savetraverse(p->next->back);
  p->next->next->bottom = false;
  savetraverse(p->next->next->back);
}
