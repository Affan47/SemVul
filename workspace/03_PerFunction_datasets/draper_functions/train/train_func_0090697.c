init_eh (void)
{
  if (! flag_exceptions)
    return;

  type_to_runtime_map = htab_create_ggc (31, t2r_hash, t2r_eq, NULL);


  if (targetm_common.except_unwind_info (&global_options) == UI_SJLJ)
    {
      tree f_jbuf, f_per, f_lsda, f_prev, f_cs, f_data, tmp;

      sjlj_fc_type_node = lang_hooks.types.make_type (RECORD_TYPE);

      f_prev = build_decl (BUILTINS_LOCATION,
			   FIELD_DECL, get_identifier ("__prev"),
			   build_pointer_type (sjlj_fc_type_node));
      DECL_FIELD_CONTEXT (f_prev) = sjlj_fc_type_node;

      f_cs = build_decl (BUILTINS_LOCATION,
			 FIELD_DECL, get_identifier ("__call_site"),
			 integer_type_node);
      DECL_FIELD_CONTEXT (f_cs) = sjlj_fc_type_node;

      tmp = build_index_type (size_int (4 - 1));
      tmp = build_array_type (lang_hooks.types.type_for_mode
				(targetm.unwind_word_mode (), 1),
			      tmp);
      f_data = build_decl (BUILTINS_LOCATION,
			   FIELD_DECL, get_identifier ("__data"), tmp);
      DECL_FIELD_CONTEXT (f_data) = sjlj_fc_type_node;

      f_per = build_decl (BUILTINS_LOCATION,
			  FIELD_DECL, get_identifier ("__personality"),
			  ptr_type_node);
      DECL_FIELD_CONTEXT (f_per) = sjlj_fc_type_node;

      f_lsda = build_decl (BUILTINS_LOCATION,
			   FIELD_DECL, get_identifier ("__lsda"),
			   ptr_type_node);
      DECL_FIELD_CONTEXT (f_lsda) = sjlj_fc_type_node;

#ifdef DONT_USE_BUILTIN_SETJMP
#ifdef JMP_BUF_SIZE
      tmp = size_int (JMP_BUF_SIZE - 1);
#else


      tmp = size_int (FIRST_PSEUDO_REGISTER + 2 - 1);
#endif
#else

      tmp = size_int (5 * BITS_PER_WORD / POINTER_SIZE - 1);
#endif
      tmp = build_index_type (tmp);
      tmp = build_array_type (ptr_type_node, tmp);
      f_jbuf = build_decl (BUILTINS_LOCATION,
			   FIELD_DECL, get_identifier ("__jbuf"), tmp);
#ifdef DONT_USE_BUILTIN_SETJMP


      DECL_ALIGN (f_jbuf) = BIGGEST_ALIGNMENT;
      DECL_USER_ALIGN (f_jbuf) = 1;
#endif
      DECL_FIELD_CONTEXT (f_jbuf) = sjlj_fc_type_node;

      TYPE_FIELDS (sjlj_fc_type_node) = f_prev;
      TREE_CHAIN (f_prev) = f_cs;
      TREE_CHAIN (f_cs) = f_data;
      TREE_CHAIN (f_data) = f_per;
      TREE_CHAIN (f_per) = f_lsda;
      TREE_CHAIN (f_lsda) = f_jbuf;

      layout_type (sjlj_fc_type_node);


      sjlj_fc_call_site_ofs
	= (tree_low_cst (DECL_FIELD_OFFSET (f_cs), 1)
	   + tree_low_cst (DECL_FIELD_BIT_OFFSET (f_cs), 1) / BITS_PER_UNIT);
      sjlj_fc_data_ofs
	= (tree_low_cst (DECL_FIELD_OFFSET (f_data), 1)
	   + tree_low_cst (DECL_FIELD_BIT_OFFSET (f_data), 1) / BITS_PER_UNIT);
      sjlj_fc_personality_ofs
	= (tree_low_cst (DECL_FIELD_OFFSET (f_per), 1)
	   + tree_low_cst (DECL_FIELD_BIT_OFFSET (f_per), 1) / BITS_PER_UNIT);
      sjlj_fc_lsda_ofs
	= (tree_low_cst (DECL_FIELD_OFFSET (f_lsda), 1)
	   + tree_low_cst (DECL_FIELD_BIT_OFFSET (f_lsda), 1) / BITS_PER_UNIT);
      sjlj_fc_jbuf_ofs
	= (tree_low_cst (DECL_FIELD_OFFSET (f_jbuf), 1)
	   + tree_low_cst (DECL_FIELD_BIT_OFFSET (f_jbuf), 1) / BITS_PER_UNIT);
    }
}
