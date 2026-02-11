jl_at(const struct jlhead *head, int pos)
{
  struct jlnode *n;

  if(head && (pos < head->len) && (pos >= 0))
    {
      for(n=head->first;n && pos;n=n->next) pos--;
      if(n && (pos == 0))
	return n->item;
    }
  return NULL;
}
