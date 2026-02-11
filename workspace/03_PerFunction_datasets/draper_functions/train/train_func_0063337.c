arc_lookup (Sym *parent, Sym *child)
{
  Arc *arc;

  if (!parent || !child)
    {
      printf ("[arc_lookup] parent == 0 || child == 0\n");
      return 0;
    }
  DBG (LOOKUPDEBUG, printf ("[arc_lookup] parent %s child %s\n",
			    parent->name, child->name));
  for (arc = parent->cg.children; arc; arc = arc->next_child)
    {
      DBG (LOOKUPDEBUG, printf ("[arc_lookup]\t parent %s child %s\n",
				arc->parent->name, arc->child->name));
      if (child->addr >= arc->child->addr
	  && child->end_addr <= arc->child->end_addr)
	{
	  return arc;
	}
    }
  return 0;
}
