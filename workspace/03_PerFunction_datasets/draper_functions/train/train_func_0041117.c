nr_typed_sisters(const Node *n, const Node *t)
{
  if (!n->sister)
    return 0;
  else if (!same(n->sister->name, t->name))
    return nr_typed_sisters(n->sister, t);
  else
    return 1 + nr_typed_sisters(n->sister, t);
}
