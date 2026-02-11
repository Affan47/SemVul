generate_protocol_list (tree i_or_p, tree klass_ctxt)
{
  tree array_type, ptype, refs_decl, lproto, e, plist;
  vec<constructor_elt, va_gc> *v = NULL;
  char buf[BUFSIZE];
  int size = 0;

  switch (TREE_CODE (i_or_p))
    {
    case CLASS_INTERFACE_TYPE:
    case CATEGORY_INTERFACE_TYPE:
      plist = CLASS_PROTOCOL_LIST (i_or_p);
      break;
    case PROTOCOL_INTERFACE_TYPE:
      plist = PROTOCOL_LIST (i_or_p);
      break;
    default:
      gcc_unreachable ();
    }


  for (lproto = plist; lproto; lproto = TREE_CHAIN (lproto))
    if (TREE_CODE (TREE_VALUE (lproto)) == PROTOCOL_INTERFACE_TYPE
	&& PROTOCOL_FORWARD_DECL (TREE_VALUE (lproto)))
      size++;


  CONSTRUCTOR_APPEND_ELT (v, NULL_TREE, build_int_cst (NULL_TREE, 0));
  e = build_int_cst (build_pointer_type (objc_protocol_template), size);
  CONSTRUCTOR_APPEND_ELT (v, NULL_TREE, e);

  for (lproto = plist; lproto; lproto = TREE_CHAIN (lproto))
    {
      tree pval = TREE_VALUE (lproto);

      if (TREE_CODE (pval) == PROTOCOL_INTERFACE_TYPE
	  && PROTOCOL_FORWARD_DECL (pval))
	{
	  tree fwref = PROTOCOL_FORWARD_DECL (pval);
	  location_t loc = DECL_SOURCE_LOCATION (fwref) ;
	  e = build_unary_op (loc, ADDR_EXPR, fwref, 0);
          CONSTRUCTOR_APPEND_ELT (v, NULL_TREE, e);
	}
    }


  switch (TREE_CODE (i_or_p))
    {
    case PROTOCOL_INTERFACE_TYPE:
      snprintf (buf, BUFSIZE, "_OBJC_ProtocolRefs_%s",
		IDENTIFIER_POINTER (PROTOCOL_NAME (i_or_p)));
      break;
    case CLASS_INTERFACE_TYPE:
      snprintf (buf, BUFSIZE, "_OBJC_ClassProtocols_%s",
		IDENTIFIER_POINTER (CLASS_NAME (i_or_p)));
      break;
    case CATEGORY_INTERFACE_TYPE:
      snprintf (buf, BUFSIZE, "_OBJC_CategoryProtocols_%s_%s",
		IDENTIFIER_POINTER (CLASS_NAME (klass_ctxt)),
		IDENTIFIER_POINTER (CLASS_SUPER_NAME (klass_ctxt)));
      break;
    default:
      gcc_unreachable ();
    }

  ptype = build_pointer_type (objc_protocol_template);
  array_type = build_sized_array_type (ptype, size + 3);
  refs_decl = start_var_decl (array_type, buf);
  OBJCMETA (refs_decl, objc_meta, meta_base);
  finish_var_decl (refs_decl,
                   objc_build_constructor (TREE_TYPE (refs_decl), v));

  return refs_decl;
}
