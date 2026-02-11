H5FD_get_mpio_atomicity(H5FD_t *_file, hbool_t *flag)
{
    H5FD_mpio_t *file = (H5FD_mpio_t*)_file;
    int          mpi_code;
    int          temp_flag;
    herr_t       ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT

#ifdef H5FDmpio_DEBUG
    if (H5FD_mpio_Debug[(int)'t'])
    	fprintf(stdout, "Entering H5FD_get_mpio_atomicity\n");
#endif


    if (MPI_SUCCESS != (mpi_code=MPI_File_get_atomicity(file->f, &temp_flag)))
        HMPI_GOTO_ERROR(FAIL, "MPI_File_get_atomicity", mpi_code)

    if (0 != temp_flag)
        *flag = TRUE;
    else
        *flag = FALSE;

done:
#ifdef H5FDmpio_DEBUG
    if (H5FD_mpio_Debug[(int)'t'])
    	fprintf(stdout, "Leaving H5FD_get_mpio_atomicity\n");
#endif
    FUNC_LEAVE_NOAPI(ret_value)
}
