jl_repl(const void *iteminlist, const void *newitem)
{
  struct jlnode *n, *nn;

  n = (struct jlnode *) _jl_hash_get(iteminlist);
  nn = (struct jlnode *) _jl_hash_get(newitem);

  if(n)
    {
      _jl_hash_del(n->item);
      n->item = (void*) newitem;
      if(nn)
	{
	  _jl_hash_del(nn->item);
	  nn->item = (void*) iteminlist;
	}
      _jl_hash_store((struct listentry*)n, newitem);
      if(nn) _jl_hash_store((struct listentry*)nn, iteminlist);
      return 0;
    }
  return -1;
}
