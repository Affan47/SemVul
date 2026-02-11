funit_is_one_signal_assigned(
  func_unit* funit
) { PROFILE(FUNIT_IS_ONE_SIGNAL_ASSIGNED);

  sig_link* sigl = funit->sig_head;

  while( (sigl != NULL) && ((sigl->sig->exp_head == NULL) || !SIGNAL_ASSIGN_FROM_DUMPFILE( sigl->sig )) ) {
    sigl = sigl->next;
  }

  PROFILE_END;

  return( sigl != NULL );

}
