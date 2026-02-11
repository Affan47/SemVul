cp_print_error_function (diagnostic_context *context,
                         diagnostic_info *diagnostic)
{
  if (diagnostic_last_function_changed (context))
    {
      const char *old_prefix = context->printer->prefix;
      char *new_prefix = diagnostic->location.file
        ? file_name_as_prefix (diagnostic->location.file)
        : NULL;

      pp_base_set_prefix (context->printer, new_prefix);

      if (current_function_decl == NULL)
        pp_base_string (context->printer, "At global scope:");
      else
        pp_printf (context->printer, "In %s `%s':",
                   function_category (current_function_decl),
                   cxx_printable_name (current_function_decl, 2));
      pp_base_newline (context->printer);

      diagnostic_set_last_function (context);
      pp_base_destroy_prefix (context->printer);
      context->printer->prefix = old_prefix;
    }
}
