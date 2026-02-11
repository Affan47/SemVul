create_field_decl_from (tree old_field, tree field_type, tree record_type,
			tree size, tree pos_list,
			vec<subst_pair> subst_list)
{
  tree t = TREE_VALUE (purpose_member (old_field, pos_list));
  tree pos = TREE_VEC_ELT (t, 0), bitpos = TREE_VEC_ELT (t, 2);
  unsigned int offset_align = tree_low_cst (TREE_VEC_ELT (t, 1), 1);
  tree new_pos, new_field;
  unsigned int i;
  subst_pair *s;

  if (CONTAINS_PLACEHOLDER_P (pos))
    FOR_EACH_VEC_ELT (subst_list, i, s)
      pos = SUBSTITUTE_IN_EXPR (pos, s->discriminant, s->replacement);


  if (TREE_CONSTANT (pos))
    new_pos = bit_from_pos (pos, bitpos);
  else
    new_pos = NULL_TREE;

  new_field
    = create_field_decl (DECL_NAME (old_field), field_type, record_type,
			 size, new_pos, DECL_PACKED (old_field),
			 !DECL_NONADDRESSABLE_P (old_field));

  if (!new_pos)
    {
      normalize_offset (&pos, &bitpos, offset_align);
      DECL_FIELD_OFFSET (new_field) = pos;
      DECL_FIELD_BIT_OFFSET (new_field) = bitpos;
      SET_DECL_OFFSET_ALIGN (new_field, offset_align);
      DECL_SIZE (new_field) = size;
      DECL_SIZE_UNIT (new_field)
	= convert (sizetype,
		   size_binop (CEIL_DIV_EXPR, size, bitsize_unit_node));
      layout_decl (new_field, DECL_OFFSET_ALIGN (new_field));
    }

  DECL_INTERNAL_P (new_field) = DECL_INTERNAL_P (old_field);
  SET_DECL_ORIGINAL_FIELD_TO_FIELD (new_field, old_field);
  DECL_DISCRIMINANT_NUMBER (new_field) = DECL_DISCRIMINANT_NUMBER (old_field);
  TREE_THIS_VOLATILE (new_field) = TREE_THIS_VOLATILE (old_field);

  return new_field;
}
