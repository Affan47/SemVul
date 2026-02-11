check_pin_entry_errs(void)
{
    const char * fcn_name = "check_pin_entry_errs()";
    herr_t result;
    H5F_t * file_ptr = NULL;
    test_entry_t * entry_ptr;

    TESTING("pin entry related errors");

    pass = TRUE;


    if ( pass ) {

        reset_entries();

        file_ptr = setup_cache((size_t)(2 * 1024),
                                (size_t)(1 * 1024));

        protect_entry(file_ptr, 0, 0);

	unprotect_entry(file_ptr, 0, 0, H5C__NO_FLAGS_SET);

        entry_ptr = &((entries[0])[0]);
    }

    if ( pass ) {

        result = H5C_pin_protected_entry((void *)entry_ptr);

        if ( result > 0 ) {

            pass = FALSE;
            failure_mssg =
                "attempt to pin an unprotected entry succeeded.\n";

        } else {

            protect_entry(file_ptr, 0, 0);

	    unprotect_entry(file_ptr, 0, 0, H5C__PIN_ENTRY_FLAG);

            protect_entry(file_ptr, 0, 0);
	}
    }

    if ( pass ) {

        result = H5C_pin_protected_entry((void *)entry_ptr);

        if ( result > 0 ) {

            pass = FALSE;
            failure_mssg =
                "attempt to pin a pinned, protected entry succeeded.\n";

        } else {

	    unprotect_entry(file_ptr, 0, 0, H5C__UNPIN_ENTRY_FLAG);

	}
    }

    if ( pass ) {

        takedown_cache(file_ptr, FALSE, FALSE);
    }

    if ( pass ) { PASSED(); } else { H5_FAILED(); }

    if ( ! pass ) {

        HDfprintf(stdout, "%s: failure_mssg = \"%s\".\n",
                  fcn_name, failure_mssg);
    }

    return (unsigned)!pass;

}
