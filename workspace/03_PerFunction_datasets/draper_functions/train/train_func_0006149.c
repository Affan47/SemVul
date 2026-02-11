generate_v1_meth_descriptor_table (tree chain, tree protocol, const char *prefix)
{
  tree method_list_template, initlist, decl;
  int size;
  vec<constructor_elt, va_gc> *v = NULL;
  char buf[BUFSIZE];

  if (!chain || !prefix)
    return NULL_TREE;

  if (!objc_method_prototype_template)
    objc_method_prototype_template = build_method_prototype_template ();

  size = list_length (chain);
  method_list_template =
	build_method_prototype_list_template (objc_method_prototype_template,
					      size);
  snprintf (buf, BUFSIZE, "%s_%s", prefix,
	    IDENTIFIER_POINTER (PROTOCOL_NAME (protocol)));

  decl = start_var_decl (method_list_template, buf);

  CONSTRUCTOR_APPEND_ELT (v, NULL_TREE, build_int_cst (NULL_TREE, size));
  initlist =
	build_descriptor_table_initializer (objc_method_prototype_template,
					    chain);
  CONSTRUCTOR_APPEND_ELT (v, NULL_TREE, initlist);
  OBJCMETA (decl, objc_meta, meta_base);
  finish_var_decl (decl, objc_build_constructor (method_list_template, v));
  return decl;
}
