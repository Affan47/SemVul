layout_conflict_p (tree type,
		   tree offset,
		   splay_tree offsets,
		   int vbases_p)
{
  splay_tree_node max_node;


  max_node = splay_tree_max (offsets);


  if (!max_node)
    return 0;

  return walk_subobject_offsets (type, check_subobject_offset, offset,
				 offsets, (tree) (max_node->key),
				 vbases_p);
}
