di_tree_forward(Ilist vec, Di_tree node, Literals dlits, Context subst)
{
  BUMP_SUB_CALLS;
  if (vec == NULL) {
    Plist p = node->u.data;
    while (p) {
      Topform c = p->v;
      Nonunit_fsub_tests++;
      if (subsumes_di(c->literals, dlits, subst))
	return p->v;
      p = p->next;
    }
    return NULL;
  }
  else {
    void *datum = NULL;
    Di_tree kid = node->u.kids;

    while (!datum && kid && kid->label <= vec->i) {
      datum = di_tree_forward(vec->next, kid, dlits, subst);
      kid = kid->next;
    }
    return datum;
  }
}
