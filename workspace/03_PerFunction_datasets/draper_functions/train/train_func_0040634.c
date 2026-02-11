dbxout_init (const char *input_file_name)
{
  char ltext_label_name[100];
  bool used_ltext_label_name = false;
  tree syms = lang_hooks.decls.getdecls ();
  const char *mapped_name;

  typevec_len = 100;
  typevec = ggc_alloc_cleared_vec_typeinfo (typevec_len);


  obstack_specify_allocation (&stabstr_ob, 0, 1, xmalloc, free);


  ASM_GENERATE_INTERNAL_LABEL (ltext_label_name, "Ltext", 0);


  if (use_gnu_debug_info_extensions && !NO_DBX_MAIN_SOURCE_DIRECTORY)
    {
      static const char *cwd;

      if (!cwd)
	{
	  cwd = get_src_pwd ();
	  if (cwd[0] == '\0')
	    cwd = "/";
	  else if (!IS_DIR_SEPARATOR (cwd[strlen (cwd) - 1]))
	    cwd = concat (cwd, "/", NULL);
	  cwd = remap_debug_filename (cwd);
	}
#ifdef DBX_OUTPUT_MAIN_SOURCE_DIRECTORY
      DBX_OUTPUT_MAIN_SOURCE_DIRECTORY (asm_out_file, cwd);
#else
      dbxout_begin_simple_stabs_desc (cwd, N_SO, get_lang_number ());
      dbxout_stab_value_label (ltext_label_name);
      used_ltext_label_name = true;
#endif
    }

  mapped_name = remap_debug_filename (input_file_name);
#ifdef DBX_OUTPUT_MAIN_SOURCE_FILENAME
  DBX_OUTPUT_MAIN_SOURCE_FILENAME (asm_out_file, mapped_name);
#else
  dbxout_begin_simple_stabs_desc (mapped_name, N_SO, get_lang_number ());
  dbxout_stab_value_label (ltext_label_name);
  used_ltext_label_name = true;
#endif

  if (used_ltext_label_name)
    {
      switch_to_section (text_section);
      targetm.asm_out.internal_label (asm_out_file, "Ltext", 0);
    }


#ifndef NO_DBX_GCC_MARKER
  dbxout_begin_simple_stabs ("gcc2_compiled.", N_OPT);
  dbxout_stab_value_zero ();
#endif

  base_input_file = lastfile = input_file_name;

  next_type_number = 1;

#ifdef DBX_USE_BINCL
  current_file = XNEW (struct dbx_file);
  current_file->next = NULL;
  current_file->file_number = 0;
  current_file->next_type_number = 1;
  next_file_number = 1;
  current_file->prev = NULL;
  current_file->bincl_status = BINCL_NOT_REQUIRED;
  current_file->pending_bincl_name = NULL;
#endif


  dbxout_typedefs (syms);

  if (preinit_symbols)
    {
      tree t;
      for (t = nreverse (preinit_symbols); t; t = TREE_CHAIN (t))
	dbxout_symbol (TREE_VALUE (t), 0);
      preinit_symbols = 0;
    }
}
