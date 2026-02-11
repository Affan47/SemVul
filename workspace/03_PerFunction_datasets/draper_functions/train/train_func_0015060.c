next_runtime_abi_02_get_category_super_ref (location_t loc ATTRIBUTE_UNUSED,
					   struct imp_entry *imp, bool inst_meth)
{

  tree super_name = CLASS_SUPER_NAME (imp->imp_template);
  tree super_class;

  if (!flag_zero_link)
    {
      super_class = objc_get_class_reference (CLASS_NAME (imp->imp_template));

      if (!inst_meth)


	   super_class =
		build_indirect_ref (input_location,
				    build_c_cast (input_location,
					build_pointer_type (objc_class_type),
					super_class),
				    RO_UNARY_STAR);
      return super_class;
    }


  super_class = (inst_meth ? objc_get_class_decl : objc_get_meta_class_decl);

  super_name = my_build_string_pointer (IDENTIFIER_LENGTH (super_name) + 1,
					IDENTIFIER_POINTER (super_name));

  return build_function_call (input_location,
			      super_class,
			      build_tree_list (NULL_TREE, super_name));
}
