backend_fatal_no_aggregate(char *type,
                                       struct ompi_communicator_t *comm,
                                       char *name, int *error_code,
                                       va_list arglist)
{
    char *arg;

    assert(!ompi_mpi_initialized || ompi_mpi_finalized);

    fflush(stdout);
    fflush(stderr);

    arg = va_arg(arglist, char*);


    if (!ompi_mpi_init_started && !ompi_mpi_initialized) {
        if (NULL != arg) {
            out("*** The %s() function was called before MPI_INIT was invoked.\n"
                "*** This is disallowed by the MPI standard.\n", arg);
        } else {
            out("*** An MPI function was called before MPI_INIT was invoked.\n"
                "*** This is disallowed by the MPI standard.\n"
                "*** Unfortunately, no further information is available on *which* MPI\n"
                "*** function was invoked, sorry.  :-(\n", NULL);
        }
        out("*** Your MPI job will now abort.\n", NULL);
    } else if (ompi_mpi_finalized) {
        if (NULL != arg) {
            out("*** The %s() function was called after MPI_FINALIZE was invoked.\n"
                "*** This is disallowed by the MPI standard.\n", arg);
        } else {
            out("*** An MPI function was called after MPI_FINALIZE was invoked.\n"
                "*** This is disallowed by the MPI standard.\n"
                "*** Unfortunately, no further information is available on *which* MPI\n"
                "*** function was invoked, sorry.  :-(\n", NULL);
        }
        out("*** Your MPI job will now abort.\n", NULL);
    }

    else {
        int len;
        char str[MPI_MAX_PROCESSOR_NAME * 2];


        if (NULL != arg) {
            out("*** An error occurred in %s\n", arg);
        } else {
            out("*** An error occurred\n", NULL);
        }

        if (NULL != name) {


            str[0] = '\0';
            len = sizeof(str) - 1;
            strncat(str, type, len);

            len -= strlen(type);
            if (len > 0) {
                strncat(str, " ", len);

                --len;
                if (len > 0) {
                    strncat(str, name, len);
                }
            }
            out("*** on %s", str);
        } else if (NULL == name) {
            out("*** on a NULL %s\n", type);
        }

        if (NULL != error_code) {
            char *tmp = ompi_mpi_errnum_get_string(*error_code);
            if (NULL != tmp) {
                out("*** %s\n", tmp);
            } else {
                char intbuf[32];
                snprintf(intbuf, 32, "%d", *error_code);
                out("*** Error code: %d (no associated error message)\n", intbuf);
            }
        }

        out("*** MPI_ERRORS_ARE_FATAL (processes in this %s will now abort,\n", type);
        out("***    and potentially your MPI job)\n", NULL);

    }
    va_end(arglist);
}
