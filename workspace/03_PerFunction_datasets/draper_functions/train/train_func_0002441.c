cbf_free_getopt_handle(cbf_getopt_handle handle) {

        void *memblock;

        cbf_failnez( cbf_clear_getopt_handle(handle) )

        memblock = (void *) handle;

        if (handle) {

            return cbf_free(&memblock, NULL);

        }

        return 0;

    }
