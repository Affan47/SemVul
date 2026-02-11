funit_find_param(
  char*      name,
  func_unit* funit
) { PROFILE(FUNIT_FIND_PARAM);

  mod_parm* mparm = NULL;

  if( funit != NULL ) {

    if( (mparm = mod_parm_find( name, funit->param_head )) == NULL ) {
      mparm = funit_find_param( name, funit->parent );
    }

  }

  PROFILE_END;

  return( mparm );

}
