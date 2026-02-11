clauses_to_ids(struct clause_ptr *p)
{
  if (p == NULL)
    return NULL;
  else {
    struct ilist *ip = get_ilist();
    ip->i = p->c->id;
    ip->next = clauses_to_ids(p->next);
    return ip;
  }
}
