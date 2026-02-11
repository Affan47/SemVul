publicly_uniquely_derived_p (tree parent, tree type)
{
  tree base = lookup_base (type, parent, ba_ignore_scope | ba_check,
			   NULL, tf_none);
  return base && base != error_mark_node;
}
