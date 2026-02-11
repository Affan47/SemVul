cbf_make_getopt_handle(cbf_getopt_handle * handle) {

        *handle = NULL;

        cbf_failnez (cbf_alloc ((void **) handle, NULL,
                                sizeof (cbf_getopt_struct), 1))

        (*handle)->optstructs = NULL;

        cbf_onfailnez (cbf_alloc ((void **) &((*handle)->optstructs),
                                  &((*handle)->optstructs_capacity),sizeof(cbf_getopt_optstruct), 10),
                       cbf_free((void **) handle, NULL))

        (*handle)->optstructs_size = 0;
        (*handle)->optind = 0;
        (*handle)->options = NULL;

        return 0;
    }
