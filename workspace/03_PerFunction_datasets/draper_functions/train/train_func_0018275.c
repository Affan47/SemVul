get_dtor (tree type, tsubst_flags_t complain)
{
  tree fn = locate_fn_flags (type, complete_dtor_identifier, NULL_TREE,
			     LOOKUP_NORMAL, complain);
  if (fn == error_mark_node)
    return NULL_TREE;
  return fn;
}
