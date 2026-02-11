pairlist_delete(pairlist p)
{
  if (p) {
    pairlist_delete(p->next);
    dispose(p->name);
    dispose(p->value);
    dispose(p);
  }
}
