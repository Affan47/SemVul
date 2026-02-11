assertion_get_funit_summary(
            func_unit*    funit,
   unsigned int* hit,
   unsigned int* excluded,
   unsigned int* total
) { PROFILE(ASSERTION_GET_FUNIT_SUMMARY);


  *hit      = 0;
  *excluded = 0;
  *total    = 0;

  if( info_suppl.part.assert_ovl == 1 ) {
    ovl_get_funit_stats( funit, hit, excluded, total );
  }

  PROFILE_END;

}
