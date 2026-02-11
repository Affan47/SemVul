operator=(const GSetBase &ref)
{
  if (this == &ref)
    return *this;
  empty();
  rehash(ref.nbuckets);
  for (Node *n = ref.first; n; n=n->next)
    {
      HNode *m = (HNode*) operator new (traits.size);
      traits.copy( (void*)m, (void*)n, 1, 0);
      insertnode(m);
    }
  return *this;
}
