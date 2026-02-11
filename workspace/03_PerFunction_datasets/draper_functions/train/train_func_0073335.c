ovl_is_assertion_module(
  const func_unit* funit
) { PROFILE(OVL_IS_ASSERTION_MODULE);

  bool        retval = FALSE;
  funit_link* funitl;

  if( (funit != NULL) && ovl_is_assertion_name( funit->name ) ) {


    funitl = funit->tf_head;
    while( (funitl != NULL) && ((strcmp( funitl->funit->name, "ovl_cover_t" ) != 0) || (funitl->funit->type != FUNIT_TASK)) ) {
      funitl = funitl->next;
    }
    retval = (funitl == NULL);

  }

  PROFILE_END;

  return( retval );

}
