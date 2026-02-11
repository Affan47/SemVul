lang_process (void)
{

  if (link_info.dynamic_list)
    lang_finalize_version_expr_head (&link_info.dynamic_list->head);

  current_target = default_target;


  lang_for_each_statement (ldlang_open_output);
  init_opb ();

  ldemul_create_output_section_statements ();


  lang_place_undefineds ();

  if (!bfd_section_already_linked_table_init ())
    einfo (_("%P%F: Failed to create hash table\n"));


  current_target = default_target;
  open_input_bfds (statement_list.head, OPEN_BFD_NORMAL);

#ifdef ENABLE_PLUGINS
  if (plugin_active_plugins_p ())
    {
      lang_statement_list_type added;
      lang_statement_list_type files, inputfiles;


      added = *stat_ptr;

      files = file_chain;
      inputfiles = input_file_chain;
      if (plugin_call_all_symbols_read ())
	einfo (_("%P%F: %s: plugin reported error after all symbols read\n"),
	       plugin_error_plugin ());

      link_info.loading_lto_outputs = TRUE;
      open_input_bfds (*added.tail, OPEN_BFD_NORMAL);

      lang_list_remove_tail (stat_ptr, &added);

      lang_list_remove_tail (&file_chain, &files);
      lang_list_remove_tail (&input_file_chain, &inputfiles);

      if (added.head != NULL)
	{


	  plugin_insert = find_replacements_insert_point ();


	  ASSERT (plugin_insert != NULL);

	  lang_list_insert_after (stat_ptr, &added,
				  &plugin_insert->header.next);

	  lang_list_insert_after (&input_file_chain, &inputfiles,
				  &plugin_insert->next_real_file);


	  if (plugin_insert->filename)
	    lang_list_insert_after (&file_chain, &files, &plugin_insert->next);
	  else
	    lang_list_insert_after (&file_chain, &files, &file_chain.head);


	  open_input_bfds (statement_list.head, OPEN_BFD_RESCAN);
	}
    }
#endif

  link_info.gc_sym_list = &entry_symbol;
  if (entry_symbol.name == NULL)
    link_info.gc_sym_list = ldlang_undef_chain_list_head;

  ldemul_after_open ();

  bfd_section_already_linked_table_free ();


  lang_check ();


  if (command_line.version_exports_section)
    lang_do_version_exports_section ();


  ldctor_build_sets ();


  lang_do_assignments (lang_mark_phase_enum);
  expld.phase = lang_first_phase_enum;


  lang_gc_sections ();


  lang_common ();


  update_wild_statements (statement_list.head);


  lang_statement_iteration++;
  map_input_to_output_sections (statement_list.head, NULL, NULL);

  process_insert_statements ();


  lang_place_orphans ();

  if (! link_info.relocatable)
    {
      asection *found;


      bfd_merge_sections (link_info.output_bfd, &link_info);


      found = bfd_get_section_by_name (link_info.output_bfd, ".text");

      if (found != NULL)
	{
	  if (config.text_read_only)
	    found->flags |= SEC_READONLY;
	  else
	    found->flags &= ~SEC_READONLY;
	}
    }


  ldemul_before_allocation ();


  lang_record_phdrs ();


  if (link_info.relro && ! link_info.relocatable)
    lang_find_relro_sections ();


  lang_size_sections (NULL, ! RELAXATION_ENABLED);


  ldemul_after_allocation ();


  lang_set_startof ();


  lang_do_assignments (lang_final_phase_enum);

  ldemul_finish ();


  if (command_line.check_section_addresses)
    lang_check_section_addresses ();

  lang_end ();
}
