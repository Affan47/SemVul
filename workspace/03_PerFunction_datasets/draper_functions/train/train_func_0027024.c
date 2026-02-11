build_protocol_initializer (tree type, tree protocol_name, tree protocol_list,
			    tree inst_methods, tree class_methods)
{
  tree expr, ttyp;
  location_t loc;
  vec<constructor_elt, va_gc> *inits = NULL;


  loc = input_location;
  ttyp = build_pointer_type (xref_tag (RECORD_TYPE,
				       get_identifier (UTAG_CLASS)));


  expr = build_int_cst (ttyp, PROTOCOL_VERSION);

  CONSTRUCTOR_APPEND_ELT (inits, NULL_TREE, expr);

  CONSTRUCTOR_APPEND_ELT (inits, NULL_TREE, protocol_name);
  CONSTRUCTOR_APPEND_ELT (inits, NULL_TREE, protocol_list);

  ttyp = objc_method_proto_list_ptr;
  if (inst_methods)
    expr = convert (ttyp, build_unary_op (loc, ADDR_EXPR, inst_methods, 0));
  else
    expr = convert (ttyp, null_pointer_node);
  CONSTRUCTOR_APPEND_ELT (inits, NULL_TREE, expr);

  if (class_methods)
    expr = convert (ttyp, build_unary_op (loc, ADDR_EXPR, class_methods, 0));
  else
    expr = convert (ttyp, null_pointer_node);
  CONSTRUCTOR_APPEND_ELT (inits, NULL_TREE, expr);

  return objc_build_constructor (type, inits);
}
