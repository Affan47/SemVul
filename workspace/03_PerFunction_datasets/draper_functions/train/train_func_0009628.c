ADIOI_FAILSAFE_OpenColl(ADIO_File fd, int rank,
	int access_mode, int *error_code)
{
    int orig_amode_excl, orig_amode_wronly;

    orig_amode_excl = access_mode;
    if ((access_mode & ADIO_CREATE) && (access_mode & ADIO_EXCL)) {


	if(rank == fd->hints->ranklist[0]) {
	    fd->access_mode = access_mode;
	    (*(fd->fns->ADIOI_xxx_Open))(fd, error_code);
	    MPI_Bcast(error_code, 1, MPI_INT, \
		    fd->hints->ranklist[0], fd->comm);

	    if (*error_code == MPI_SUCCESS)
		(*(fd->fns->ADIOI_xxx_Close))(fd, error_code);
	}
	else MPI_Bcast(error_code, 1, MPI_INT,
		fd->hints->ranklist[0], fd->comm);
	if (*error_code != MPI_SUCCESS) {
	    return;
	}
	else {

	    access_mode = access_mode ^ ADIO_EXCL;
	}
    }

    if (fd->hints->deferred_open ) {
        if (fd->agg_comm == MPI_COMM_NULL) {


            fd->access_mode = orig_amode_excl;
            *error_code = MPI_SUCCESS;
            return;
        }
    }


    orig_amode_wronly = access_mode;
    if (access_mode & ADIO_WRONLY) {
	access_mode = access_mode ^ ADIO_WRONLY;
	access_mode = access_mode | ADIO_RDWR;
    }
    fd->access_mode = access_mode;

    (*(fd->fns->ADIOI_xxx_Open))(fd, error_code);


    fd->access_mode = orig_amode_wronly;
    if (*error_code != MPI_SUCCESS)
        (*(fd->fns->ADIOI_xxx_Open))(fd, error_code);

    if(*error_code != MPI_SUCCESS) return;

    if (fd->access_mode != orig_amode_excl) fd->access_mode = orig_amode_excl;


    fd->is_open = 1;
}
