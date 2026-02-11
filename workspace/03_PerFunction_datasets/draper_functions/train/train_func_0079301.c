lookup_type_for_runtime (tree type)
{
  tree *slot;


  if (TREE_CODE (type) == NOP_EXPR)
    return type;

  slot = (tree *) htab_find_slot_with_hash (type_to_runtime_map, type,
					    TREE_HASH (type), NO_INSERT);


  return TREE_VALUE (*slot);
}
