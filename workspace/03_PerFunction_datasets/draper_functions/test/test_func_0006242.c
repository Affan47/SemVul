create_loop_fn (location_t loc)
{
  char buf[100];
  char *tname;
  tree decl, type, name, t;
  struct function *act_cfun = cfun;
  static unsigned loopfn_num;

  loc = LOCATION_LOCUS (loc);
  snprintf (buf, 100, "%s.$loopfn", current_function_name ());
  ASM_FORMAT_PRIVATE_NAME (tname, buf, loopfn_num++);
  clean_symbol_name (tname);
  name = get_identifier (tname);
  type = build_function_type_list (void_type_node, ptr_type_node, NULL_TREE);

  decl = build_decl (loc, FUNCTION_DECL, name, type);
  if (!parallelized_functions)
    parallelized_functions = BITMAP_GGC_ALLOC ();
  bitmap_set_bit (parallelized_functions, DECL_UID (decl));

  TREE_STATIC (decl) = 1;
  TREE_USED (decl) = 1;
  DECL_ARTIFICIAL (decl) = 1;
  DECL_IGNORED_P (decl) = 0;
  TREE_PUBLIC (decl) = 0;
  DECL_UNINLINABLE (decl) = 1;
  DECL_EXTERNAL (decl) = 0;
  DECL_CONTEXT (decl) = NULL_TREE;
  DECL_INITIAL (decl) = make_node (BLOCK);

  t = build_decl (loc, RESULT_DECL, NULL_TREE, void_type_node);
  DECL_ARTIFICIAL (t) = 1;
  DECL_IGNORED_P (t) = 1;
  DECL_RESULT (decl) = t;

  t = build_decl (loc, PARM_DECL, get_identifier (".paral_data_param"),
		  ptr_type_node);
  DECL_ARTIFICIAL (t) = 1;
  DECL_ARG_TYPE (t) = ptr_type_node;
  DECL_CONTEXT (t) = decl;
  TREE_USED (t) = 1;
  DECL_ARGUMENTS (decl) = t;

  allocate_struct_function (decl, false);


  set_cfun (act_cfun);

  return decl;
}
