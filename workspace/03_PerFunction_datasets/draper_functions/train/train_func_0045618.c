xtensa_layout_wild (const reloc_deps_graph *deps, lang_wild_statement_type *w)
{


  lang_statement_union_type **s_p;
#if EXTRA_VALIDATION
  size_t old_count, new_count;
  size_t ct1, ct2;
#endif

  lang_wild_statement_type literal_wild;
  literal_wild.header.next = NULL;
  literal_wild.header.type = lang_wild_statement_enum;
  literal_wild.filename = NULL;
  literal_wild.filenames_sorted = FALSE;
  literal_wild.section_list = NULL;
  literal_wild.keep_sections = FALSE;
  literal_wild.children.head = NULL;
  literal_wild.children.tail = &literal_wild.children.head;

#if EXTRA_VALIDATION
  old_count = ld_count_children ((lang_statement_union_type*) w);
#endif

  s_p = &w->children.head;
  while (*s_p != NULL)
    {
      lang_statement_union_type *l = *s_p;
      if (l->header.type == lang_input_section_enum)
	{
	  if (section_is_target (deps, l)
	      && ! section_is_source (deps, l))
	    {

	      *s_p = l->header.next;
	      if (*s_p == NULL)
		w->children.tail = s_p;
	      l->header.next = NULL;


	      *literal_wild.children.tail = l;
	      literal_wild.children.tail = &l->header.next;
	      continue;
	    }
	}
      s_p = &(*s_p)->header.next;
    }

#if EXTRA_VALIDATION
  ct1 = ld_count_children ((lang_statement_union_type*) w);
  ct2 = ld_count_children ((lang_statement_union_type*) &literal_wild);

  ASSERT (old_count == (ct1 + ct2));
#endif


  while (literal_wild.children.head != NULL)
    {
      lang_statement_union_type *lit = literal_wild.children.head;
      bfd_boolean placed = FALSE;

#if EXTRA_VALIDATION
      ASSERT (ct2 > 0);
      ct2--;
#endif


      literal_wild.children.head = lit->header.next;
      if (literal_wild.children.head == NULL)
	literal_wild.children.tail = &literal_wild.children.head;
      lit->header.next = NULL;


      for (s_p = &w->children.head; *s_p != NULL; s_p = &(*s_p)->header.next)
	{
	  lang_statement_union_type *src = *s_p;
	  if (deps_has_edge (deps, src, lit))
	    {

	      lit->header.next = *s_p;
	      *s_p = lit;
	      placed = TRUE;
	      break;
	    }
	}

      if (!placed)
	{

	  *w->children.tail = lit;
	  w->children.tail = &lit->header.next;
	}
    }

#if EXTRA_VALIDATION
  new_count = ld_count_children ((lang_statement_union_type*) w);
  ASSERT (new_count == old_count);
#endif
}
