operator= (const GListBase & ref)
{
  if (this == &ref)
    return *this;
  empty();
  for(Node *n = ref.head.next; n; n=n->next)
    {
      Node *m = (Node*) operator new (traits.size);
      traits.copy( (void*)m, (void*)n, 1, 0);
      append(m);
    }
  return *this;
}
