alias_sets_conflict_p (HOST_WIDE_INT set1, HOST_WIDE_INT set2)
{
  alias_set_entry ase;


  if (set1 == 0 || set2 == 0

      || set1 == set2)
    return 1;


  ase = get_alias_set_entry (set1);
  if (ase != 0
      && (ase->has_zero_child
	  || splay_tree_lookup (ase->children,
				(splay_tree_key) set2)))
    return 1;


  ase = get_alias_set_entry (set2);
  if (ase != 0
      && (ase->has_zero_child
	  || splay_tree_lookup (ase->children,
				(splay_tree_key) set1)))
    return 1;


  return 0;
}
