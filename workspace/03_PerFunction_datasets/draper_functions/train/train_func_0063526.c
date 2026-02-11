lookup_field_for_decl (struct nesting_info *info, tree decl,
		       enum insert_option insert)
{
  void **slot;

  if (insert == NO_INSERT)
    {
      slot = pointer_map_contains (info->field_map, decl);
      return slot ? (tree) *slot : NULL_TREE;
    }

  slot = pointer_map_insert (info->field_map, decl);
  if (!*slot)
    {
      tree field = make_node (FIELD_DECL);
      DECL_NAME (field) = DECL_NAME (decl);

      if (use_pointer_in_frame (decl))
	{
	  TREE_TYPE (field) = build_pointer_type (TREE_TYPE (decl));
	  DECL_ALIGN (field) = TYPE_ALIGN (TREE_TYPE (field));
	  DECL_NONADDRESSABLE_P (field) = 1;
	}
      else
	{
          TREE_TYPE (field) = TREE_TYPE (decl);
          DECL_SOURCE_LOCATION (field) = DECL_SOURCE_LOCATION (decl);
          DECL_ALIGN (field) = DECL_ALIGN (decl);
          DECL_USER_ALIGN (field) = DECL_USER_ALIGN (decl);
          TREE_ADDRESSABLE (field) = TREE_ADDRESSABLE (decl);
          DECL_NONADDRESSABLE_P (field) = !TREE_ADDRESSABLE (decl);
          TREE_THIS_VOLATILE (field) = TREE_THIS_VOLATILE (decl);
	}

      insert_field_into_struct (get_frame_type (info), field);
      *slot = field;

      if (TREE_CODE (decl) == PARM_DECL)
	info->any_parm_remapped = true;
    }

  return (tree) *slot;
}
