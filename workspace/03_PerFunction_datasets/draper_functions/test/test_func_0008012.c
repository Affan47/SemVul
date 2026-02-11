ld_xtensa_insert_page_offsets (bfd_vma dot,
			       lang_statement_union_type *s,
			       reloc_deps_graph *deps,
			       bfd_boolean lit_align)
{
  xtensa_ld_iter_stack *stack = NULL;
  xtensa_ld_iter_stack **stack_p = &stack;

  bfd_boolean first_section = FALSE;
  bfd_boolean in_literals = FALSE;

  if (!lit_align)
    return FALSE;

  for (iter_stack_create (stack_p, s);
       !iter_stack_empty (stack_p);
       iter_stack_next (stack_p))
    {
      lang_statement_union_type *l = iter_stack_current (stack_p);

      switch (l->header.type)
	{
	case lang_input_section_enum:
	  {
	    asection *section = l->input_section.section;
	    bfd_boolean do_xtensa_alignment = FALSE;

	    if (lit_align)
	      {
		if (section->size != 0
		    && (first_section
			|| (in_literals && !section_is_target (deps, l))
			|| (!in_literals && section_is_target (deps, l))))
		  {
		    do_xtensa_alignment = TRUE;
		  }
		first_section = FALSE;
		if (section->size != 0)
		  {
		    in_literals = (section_is_target (deps, l)
				   && !section_is_source (deps, l));
		  }
	      }

	    if (do_xtensa_alignment && xtensa_page_power != 0)
	      {


		etree_type *name_op = exp_nameop (NAME, ".");
		etree_type *addend_op = exp_intop (1 << xtensa_page_power);
		etree_type *add_op = exp_binop ('+', name_op, addend_op);
		etree_type *assign_op = exp_assign (".", add_op, FALSE);

		lang_assignment_statement_type *assign_stmt;
		lang_statement_union_type *assign_union;
		lang_statement_list_type tmplist;


		lang_list_init (&tmplist);
		push_stat_ptr (&tmplist);

		assign_stmt = lang_add_assignment (assign_op);
		assign_union = (lang_statement_union_type *) assign_stmt;
		pop_stat_ptr ();

		assign_union->header.next = l;
		*(*stack_p)->iterloc.loc = assign_union;
		iter_stack_next (stack_p);
	      }
	  }
	  break;
	default:
	  break;
	}
    }
  return dot;
}
