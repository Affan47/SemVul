ompi_mpi_errnum_add_string(int errnum, const char *errstring, int len)
{
    ompi_mpi_errcode_t *errcodep;

    errcodep = (ompi_mpi_errcode_t *)opal_pointer_array_get_item(&ompi_mpi_errcodes, errnum);
    if ( NULL == errcodep ) {
        return OMPI_ERROR;
    }

    if ( MPI_MAX_ERROR_STRING > len ) {
        len = MPI_MAX_ERROR_STRING;
    }

    strncpy ( errcodep->errstring, errstring, len );
    return OMPI_SUCCESS;
}
