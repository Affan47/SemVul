for_each_template_parm (tree t, tree_fn_t fn, void* data, htab_t visited)
{
  struct pair_fn_data pfd;
  int result;


  pfd.fn = fn;
  pfd.data = data;


  if (visited)
    pfd.visited = visited;
  else
    pfd.visited = htab_create (37, htab_hash_pointer, htab_eq_pointer,
			       NULL);
  result = walk_tree (&t,
		      for_each_template_parm_r,
		      &pfd,
		      pfd.visited) != NULL_TREE;


  if (!visited)
    htab_delete (pfd.visited);

  return result;
}
