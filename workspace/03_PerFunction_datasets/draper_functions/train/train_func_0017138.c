InstallNativeFunctions() {
  HandleScope scope;
  INSTALL_NATIVE(JSFunction, "CreateDate", create_date_fun);
  INSTALL_NATIVE(JSFunction, "ToNumber", to_number_fun);
  INSTALL_NATIVE(JSFunction, "ToString", to_string_fun);
  INSTALL_NATIVE(JSFunction, "ToDetailString", to_detail_string_fun);
  INSTALL_NATIVE(JSFunction, "ToObject", to_object_fun);
  INSTALL_NATIVE(JSFunction, "ToInteger", to_integer_fun);
  INSTALL_NATIVE(JSFunction, "ToUint32", to_uint32_fun);
  INSTALL_NATIVE(JSFunction, "ToInt32", to_int32_fun);
  INSTALL_NATIVE(JSFunction, "GlobalEval", global_eval_fun);
  INSTALL_NATIVE(JSFunction, "Instantiate", instantiate_fun);
  INSTALL_NATIVE(JSFunction, "ConfigureTemplateInstance",
                 configure_instance_fun);
  INSTALL_NATIVE(JSFunction, "MakeMessage", make_message_fun);
  INSTALL_NATIVE(JSFunction, "GetStackTraceLine", get_stack_trace_line_fun);
  INSTALL_NATIVE(JSObject, "functionCache", function_cache);
}
