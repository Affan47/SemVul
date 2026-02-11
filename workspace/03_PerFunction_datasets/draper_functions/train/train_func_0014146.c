xsh_parameters_generic( const char *recipe_id,
			     cpl_parameterlist * plist )
{
  XSH_ASSURE_NOT_NULL( recipe_id ) ;
  XSH_ASSURE_NOT_NULL( plist ) ;

  check( xsh_parameters_new_string( plist, recipe_id, "keep-temp", "no",
	 "If 'no', temporary files are deleted." ) ) ;
  check( xsh_parameters_new_string( plist, recipe_id, "debug-level",
				    "none",
  "Additional xshooter debug level. One of 'none', 'low', 'medium', 'high'"));


  check( xsh_parameters_new_boolean(plist,recipe_id, "time-stamp",
				    FALSE,
				    "Add timestamp to product file name." )) ;

 cleanup:
  return ;
}
