funit_find_signal(
  char*      name,
  func_unit* funit
) { PROFILE(FUNIT_FIND_SIGNAL);

  vsignal*    found_sig = NULL;
  vsignal     sig;
  sig_link*   sigl;
#ifndef VPI_ONLY
  gen_item*   gi;
  gen_item*   found_gi;
  gitem_link* gil;
#endif

  sig.name = name;


  if( (sigl = sig_link_find( name, funit->sig_head )) != NULL ) {

    found_sig = sigl->sig;

#ifndef VPI_ONLY
  } else {


    gi = gen_item_create_sig( &sig );

    if( ((gil = gitem_link_find( gi, funit->gitem_head )) != NULL) && ((found_gi = gen_item_find( gil->gi, gi )) != NULL) ) {
      found_sig = found_gi->elem.sig;
    }


    gen_item_dealloc( gi, FALSE );
#endif

  }

  PROFILE_END;

  return( found_sig );

}
