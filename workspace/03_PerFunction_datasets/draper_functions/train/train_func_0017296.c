objc_generate_v1_next_metadata (void)
{
  struct imp_entry *impent;
  tree chain, attr;
  long vers;


  if (objc_static_instances)
    gcc_unreachable ();

  build_metadata_templates ();
  objc_implementation_context =
  implementation_template =
  UOBJC_CLASS_decl =
  UOBJC_METACLASS_decl = NULL_TREE;

  for (impent = imp_list; impent; impent = impent->next)
    {


      if (flag_gen_declaration)
	dump_interface (gen_declaration_file, impent->imp_context);


      if (TREE_CODE (impent->imp_context) == CLASS_IMPLEMENTATION_TYPE)
	generate_v1_class_structs (impent);
      else
	generate_v1_category (impent);
    }


  build_next_selector_translation_table ();

  if (protocol_chain)
    generate_v1_protocols ();


  if (imp_count || cat_count)
    generate_objc_symtab_decl ();

  vers = OBJC_VERSION;
  attr = build_tree_list (objc_meta, meta_modules);
  build_module_descriptor (vers, attr);


  generate_objc_image_info ();


  for (chain = cls_ref_chain; chain; chain = TREE_CHAIN (chain))
    {
      handle_next_class_ref (chain);
      if (TREE_PURPOSE (chain))
	generate_classref_translation_entry (chain);
    }

  for (impent = imp_list; impent; impent = impent->next)
    handle_next_impent (impent);


  generate_strings ();
}
