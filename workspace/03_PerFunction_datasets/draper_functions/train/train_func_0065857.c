build_exception_object_var (void)
{
  tree decl = DECL_FUNCTION_EXC_OBJ (current_function_decl);
  if (decl == NULL)
    {
      decl = build_decl (DECL_SOURCE_LOCATION (current_function_decl),
			 VAR_DECL, get_identifier ("#exc_obj"), ptr_type_node);
      DECL_IGNORED_P (decl) = 1;
      DECL_ARTIFICIAL (decl) = 1;

      DECL_FUNCTION_EXC_OBJ (current_function_decl) = decl;
      pushdecl_function_level (decl);
    }
  return decl;
}
