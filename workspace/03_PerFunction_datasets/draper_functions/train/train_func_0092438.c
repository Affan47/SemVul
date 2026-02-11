xsh_parameters_use_model_get( const char * recipe_id,
				  const cpl_parameterlist * plist )
{
  char * yesno = NULL ;

  XSH_ASSURE_NOT_NULL( recipe_id ) ;
  XSH_ASSURE_NOT_NULL( plist ) ;

  yesno = xsh_parameters_get_string( plist, recipe_id, "use-model" ) ;

  if ( strcmp( yesno, "yes" ) == 0 ) return 1 ;
  else return 0 ;

 cleanup:
  return 0 ;
}
