gen_array_type_die (type, context_die)
     tree type;
     dw_die_ref context_die;
{
  dw_die_ref scope_die = scope_die_for (type, context_die);
  dw_die_ref array_die;
  tree element_type;


#ifdef MIPS_DEBUGGING_INFO
  gen_type_die (TREE_TYPE (type), context_die);
#endif

  array_die = new_die (DW_TAG_array_type, scope_die, type);
  add_name_attribute (array_die, type_tag (type));
  equate_type_number_to_die (type, array_die);

  if (TREE_CODE (type) == VECTOR_TYPE)
    {


      type = TREE_TYPE (TYPE_FIELDS (TYPE_DEBUG_REPRESENTATION_TYPE (type)));
      add_AT_flag (array_die, DW_AT_GNU_vector, 1);
    }

#if 0


  add_AT_unsigned (array_die, DW_AT_ordering, DW_ORD_row_major);
#endif

#ifdef MIPS_DEBUGGING_INFO


  if (! TYPE_DOMAIN (type))
    add_AT_unsigned (array_die, DW_AT_declaration, 1);
  else
#endif
    add_subscript_info (array_die, type);


  element_type = TREE_TYPE (type);


#ifndef MIPS_DEBUGGING_INFO
  while (TREE_CODE (element_type) == ARRAY_TYPE)
    element_type = TREE_TYPE (element_type);

  gen_type_die (element_type, context_die);
#endif

  add_type_attribute (array_die, element_type, 0, 0, context_die);
}
