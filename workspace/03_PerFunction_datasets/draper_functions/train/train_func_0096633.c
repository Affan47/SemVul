break_out_comdat_types (dw_die_ref die)
{
  dw_die_ref c;
  dw_die_ref first;
  dw_die_ref prev = NULL;
  dw_die_ref next = NULL;
  dw_die_ref unit = NULL;

  first = c = die->die_child;
  if (c)
    next = c->die_sib;
  if (c) do {
    if (prev == NULL || prev->die_sib == c)
      prev = c;
    c = next;
    next = (c == first ? NULL : c->die_sib);
    if (should_move_die_to_comdat (c))
      {
        dw_die_ref replacement;
	comdat_type_node_ref type_node;


        unit = new_die (DW_TAG_type_unit, NULL, NULL);
        add_AT_unsigned (unit, DW_AT_language,
                         get_AT_unsigned (comp_unit_die (), DW_AT_language));
        type_node = ggc_alloc_cleared_comdat_type_node ();
        type_node->root_die = unit;
        type_node->next = comdat_type_list;
        comdat_type_list = type_node;


        generate_type_signature (c, type_node);


	replacement = remove_child_or_replace_with_skeleton (unit, c, prev);
	type_node->skeleton_die = replacement;


        break_out_comdat_types (c);


	add_child_die (unit, c);

        if (replacement != NULL)
          c = replacement;
      }
    else if (c->die_tag == DW_TAG_namespace
             || c->die_tag == DW_TAG_class_type
             || c->die_tag == DW_TAG_structure_type
             || c->die_tag == DW_TAG_union_type)
      {

        break_out_comdat_types (c);
      }
  } while (next != NULL);
}
