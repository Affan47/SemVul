objc_start_protocol (tree name, tree protos, tree attributes)
{
  if (flag_objc1_only && attributes)
    error_at (input_location, "protocol attributes are not available in Objective-C 1.0");

  objc_interface_context
    = start_protocol (PROTOCOL_INTERFACE_TYPE, name, protos, attributes);
  objc_method_optional_flag = false;
}
