p_di_tree(Ilist vec, Di_tree node, int depth)
{
  int i;
  for (i = 0; i < depth; i++)
    printf(" ");
  if (vec == NULL) {
    Plist p = node->u.data;
    printf("IDs:");
    while (p) {
      Topform c = p->v;
      printf(" %d", c->id);
      p = p->next;
    }
    printf("\n");
  }
  else {
    Di_tree kid;
    printf("%d\n", node->label);
    for (kid = node->u.kids; kid; kid = kid->next)
      p_di_tree(vec->next, kid, depth+1);
  }
}
