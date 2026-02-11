detach_all()
{
  LOCK(&lock);
  Cacheable * p = first;
  while (p) {
    *p->prev = 0;
    p->prev = 0;
    p = p->next;
  }
}
