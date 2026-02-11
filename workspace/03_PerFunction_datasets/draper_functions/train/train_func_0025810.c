check_move_entry(void)
{
    const char * fcn_name = "check_move_entry";
    int          i;
    H5F_t *      file_ptr = NULL;
    struct move_entry_test_spec test_specs[4] =
    {
      {
         PICO_ENTRY_TYPE,
         10,
	 FALSE,
	 FALSE
      },
      {
         PICO_ENTRY_TYPE,
         20,
	 TRUE,
	 FALSE
      },
      {
         PICO_ENTRY_TYPE,
         30,
	 FALSE,
	 TRUE
      },
      {
         PICO_ENTRY_TYPE,
         40,
	 TRUE,
	 TRUE
      }
    };

    TESTING("H5C_move_entry() functionality");

    pass = TRUE;


    if ( pass ) {

        reset_entries();

        file_ptr = setup_cache((size_t)(2 * 1024 * 1024),
                                (size_t)(1 * 1024 * 1024));
    }

    i = 0;
    while ( ( pass ) && ( i < 4 ) )
    {
        check_move_entry__run_test(file_ptr, i, &(test_specs[i]));
	i++;
    }

    if ( pass ) {

        takedown_cache(file_ptr, FALSE, FALSE);
    }

    if ( pass ) { PASSED(); } else { H5_FAILED(); }

    if ( ! pass ) {

        HDfprintf(stdout, "%s(): failure_mssg = \"%s\".\n",
                  fcn_name, failure_mssg);
    }

    return (unsigned)!pass;

}
