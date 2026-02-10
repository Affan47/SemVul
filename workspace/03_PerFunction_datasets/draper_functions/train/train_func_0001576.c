declare_global(lexid *name, decl *value)
{
  ste *p = find(name);

#ifdef DEBUG_SYMTAB
  printf("Declaring %s globally in scope %d, depth %d\n",
	 name->getname(),
	 scopes[globalscope],
	 globalscope);
#endif
  if ( p != NULL && p->getscope() == globalscope )
    {
      Error.Error ("%s already defined in global scope.",name->getname() );
      return (p);
    }

  p = new ste(name, scopes[ globalscope ], value);


  p->next = scopestack[ globalscope ];
  ste *oldtop = scopestack[ globalscope ];
  scopestack[ globalscope ] = p;


  int i = globalscope + 1;
  ste *q = NULL;
  while ( scopestack[i] == oldtop )
    {
      scopestack[i] = p;
      i++;
    }
  if (i <= scopedepth )
    {
      q = scopestack[i];
      while ( q->next->scope == q->scope)
	{
	  q = q->next;
	}
      q->next = p;
    }
  return (p);
}
