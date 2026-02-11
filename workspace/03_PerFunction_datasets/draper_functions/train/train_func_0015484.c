update_wild_statements (lang_statement_union_type *s)
{
  struct wildcard_list *sec;

  switch (sort_section)
    {
    default:
      FAIL ();

    case none:
      break;

    case by_name:
    case by_alignment:
      for (; s != NULL; s = s->header.next)
	{
	  switch (s->header.type)
	    {
	    default:
	      break;

	    case lang_wild_statement_enum:
	      for (sec = s->wild_statement.section_list; sec != NULL;
		   sec = sec->next)
		{
		  switch (sec->spec.sorted)
		    {
		    case none:
		      sec->spec.sorted = sort_section;
		      break;
		    case by_name:
		      if (sort_section == by_alignment)
			sec->spec.sorted = by_name_alignment;
		      break;
		    case by_alignment:
		      if (sort_section == by_name)
			sec->spec.sorted = by_alignment_name;
		      break;
		    default:
		      break;
		    }
		}
	      break;

	    case lang_constructors_statement_enum:
	      update_wild_statements (constructor_list.head);
	      break;

	    case lang_output_section_statement_enum:

	      if (strcmp (s->output_section_statement.name, ".init") != 0
		  && strcmp (s->output_section_statement.name, ".fini") != 0)
		update_wild_statements
		  (s->output_section_statement.children.head);
	      break;

	    case lang_group_statement_enum:
	      update_wild_statements (s->group_statement.children.head);
	      break;
	    }
	}
      break;
    }
}
