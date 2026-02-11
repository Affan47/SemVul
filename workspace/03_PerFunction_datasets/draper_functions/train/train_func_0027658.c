walk_aliased_vdefs (ao_ref *ref, tree vdef,
		    bool (*walker)(ao_ref *, tree, void *), void *data,
		    bitmap *visited)
{
  bitmap local_visited = NULL;
  unsigned int ret;

  timevar_push (TV_ALIAS_STMT_WALK);

  ret = walk_aliased_vdefs_1 (ref, vdef, walker, data,
			      visited ? visited : &local_visited, 0);
  if (local_visited)
    BITMAP_FREE (local_visited);

  timevar_pop (TV_ALIAS_STMT_WALK);

  return ret;
}
