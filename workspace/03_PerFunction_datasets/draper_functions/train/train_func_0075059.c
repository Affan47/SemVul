filltraverse(node *pb, node *qb, boolean contin)
{
  if (qb->tip)
    return;
  if (contin) {
    filltraverse(pb, qb->next->back,contin);
    filltraverse(pb, qb->next->next->back,contin);
    nudists(qb, pb);
    return;
  }
  if (!qb->next->back->tip)
    nudists(qb->next->back, pb);
  if (!qb->next->next->back->tip)
    nudists(qb->next->next->back, pb);
}
