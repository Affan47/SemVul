objc_set_method_opt (bool optional)
{
  if (flag_objc1_only)
    {
      if (optional)
	error_at (input_location, "%<@optional%> is not available in Objective-C 1.0");
      else
	error_at (input_location, "%<@required%> is not available in Objective-C 1.0");
    }

  objc_method_optional_flag = optional;
  if (!objc_interface_context
      || TREE_CODE (objc_interface_context) != PROTOCOL_INTERFACE_TYPE)
    {
      if (optional)
	error ("%<@optional%> is allowed in @protocol context only");
      else
	error ("%<@required%> is allowed in @protocol context only");
      objc_method_optional_flag = false;
    }
}
