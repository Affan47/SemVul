report_generate(
  FILE* ofile
) { PROFILE(REPORT_GENERATE);

  report_print_header( ofile );


  if( report_instance ) {
    inst_link* instl = db_list[curr_db]->inst_head;
    while( instl != NULL ) {
      report_gather_instance_stats( instl->inst );
      instl = instl->next;
    }
  } else {
    report_gather_funit_stats( db_list[curr_db]->funit_head );
  }


  if( report_line ) {
    line_report( ofile, (report_comb_depth != REPORT_SUMMARY) );
  }

  if( report_toggle ) {
    toggle_report( ofile, (report_comb_depth != REPORT_SUMMARY) );
  }

  if( report_memory ) {
    memory_report( ofile, (report_comb_depth != REPORT_SUMMARY) );
  }

  if( report_combination ) {
    combination_report( ofile, (report_comb_depth != REPORT_SUMMARY) );
  }

  if( report_fsm ) {
    fsm_report( ofile, (report_comb_depth != REPORT_SUMMARY) );
  }

  if( report_assertion ) {
    assertion_report( ofile, (report_comb_depth != REPORT_SUMMARY) );
  }

  if( report_race ) {
    race_report( ofile, (report_comb_depth != REPORT_SUMMARY) );
  }

  PROFILE_END;

}
