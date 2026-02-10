objc_add_method_declaration (bool is_class_method, tree decl, tree attributes)
{
  if (!objc_interface_context)
    {


      fatal_error ("method declaration not in @interface context");
    }

  if (flag_objc1_only && attributes)
    error_at (input_location, "method attributes are not available in Objective-C 1.0");

  objc_decl_method_attributes (&decl, attributes, 0);
  objc_add_method (objc_interface_context,
		   decl,
		   is_class_method,
		   objc_method_optional_flag);
}
