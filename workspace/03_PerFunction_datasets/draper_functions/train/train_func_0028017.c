reroot(node *outgroup)
{

  node *p, *q, *newbottom, *oldbottom;
  boolean onleft;

  if (outgroup->back->index == root->index)
    return;
  newbottom = outgroup->back;
  p = treenode[newbottom->index - 1]->back;
  while (p->index != root->index) {
    oldbottom = treenode[p->index - 1];
    treenode[p->index - 1] = p;
    p = oldbottom->back;
  }
  onleft = (p == root->next);
  if (restoring)
    if (!onleft && wasleft){
      p = root->next->next;
      q = root->next;
    } else {
      p = root->next;
      q = root->next->next;
    }
  else {
    if (onleft)
      oldoutgrno = root->next->next->back->index;
    else
      oldoutgrno = root->next->back->index;
    wasleft = onleft;
    p = root->next;
    q = root->next->next;
  }
  p->back->back = q->back;
  q->back->back = p->back;
  p->back = outgroup;
  q->back = outgroup->back;
  if (restoring) {
    if (!onleft && wasleft) {
      outgroup->back->back = root->next;
      outgroup->back = root->next->next;
    } else {
      outgroup->back->back = root->next->next;
      outgroup->back = root->next;
    }
  } else {
    outgroup->back->back = root->next->next;
    outgroup->back = root->next;
  }
  treenode[newbottom->index - 1] = newbottom;
}
