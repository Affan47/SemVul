addtraverse(node *a, node *b, node *c, placeptr place,
                valptr valyew, long *n)
{

  if (done)
    return;
  add(a, b, c, &root, treenode);
  (*n)++;
  evaluate(root);
  examined++;
  if (examined == howoften) {
    examined = 0;
    mults++;
    if (mults == howmany)
      done = true;
    if (progress) {
      printf("%6ld",mults);
      if (bestyet >= 0)
        printf("%18.5f", bestyet);
      else
        printf("         -        ");
      printf("%17ld%20.2f\n", nextree - 1, fracdone * 100);
#ifdef WIN32
      phyFillScreenColor();
#endif
    }
  }
  valyew[*n - 1] = like;
  place[*n - 1] = a->index;
  re_move(&b, &c, &root, treenode);
  if (!a->tip) {
    addtraverse(a->next->back, b, c, place,valyew,n);
    addtraverse(a->next->next->back, b, c, place,valyew,n);
  }
}
