build_objc_method_call (location_t loc, int super_flag, tree method_prototype,
			tree lookup_object, tree selector,
			tree method_params)
{
  tree sender, sender_cast, method, t;
  tree rcv_p = (super_flag ? objc_super_type : objc_object_type);
  vec<tree, va_gc> *parms;
  unsigned nparm = (method_params ? list_length (method_params) : 0);


  tree ret_type
    = (method_prototype
       ? TREE_VALUE (TREE_TYPE (method_prototype))
       : objc_object_type);
  tree ftype = build_function_type_for_method (ret_type, method_prototype,
					       METHOD_REF, super_flag);

  if (method_prototype && METHOD_TYPE_ATTRIBUTES (method_prototype))
    ftype = build_type_attribute_variant (ftype,
					  METHOD_TYPE_ATTRIBUTES
					  (method_prototype));

  sender_cast = build_pointer_type (ftype);

  lookup_object = build_c_cast (loc, rcv_p, lookup_object);


  lookup_object = save_expr (lookup_object);


  vec_alloc (parms, nparm + 2);


  if (!targetm.calls.struct_value_rtx (0, 0)
      && (TREE_CODE (ret_type) == RECORD_TYPE
	  || TREE_CODE (ret_type) == UNION_TYPE)
      && targetm.calls.return_in_memory (ret_type, 0))
    sender = (super_flag ? umsg_super_stret_decl
			 : flag_nil_receivers ? umsg_stret_decl
					      : umsg_nonnil_stret_decl);
  else
    sender = (super_flag ? umsg_super_decl
			 : (flag_nil_receivers  ? (flag_objc_direct_dispatch
							? umsg_fast_decl
							: umsg_decl)
						: umsg_nonnil_decl));
  method = build_fold_addr_expr_loc (loc, sender);


  parms->quick_push (lookup_object);

  parms->quick_push (selector);

  if (nparm)
    for (; method_params; method_params = TREE_CHAIN (method_params))
      parms->quick_push (TREE_VALUE (method_params));


  t = build3 (OBJ_TYPE_REF, sender_cast, method,
			    lookup_object, size_zero_node);
  t = build_function_call_vec (loc, t, parms, NULL);
  vec_free (parms);
  return t;
}
