ADIOI_GEN_Prealloc(ADIO_File fd, ADIO_Offset diskspace, int *error_code)
{
	ADIO_Offset curr_fsize, alloc_size, size, len, done;
	ADIO_Status status;
	int i, ntimes;
	char *buf;
	ADIO_Fcntl_t *fcntl_struct;
	static char myname[] = "ADIOI_GEN_PREALLOC";


	fcntl_struct = (ADIO_Fcntl_t *) ADIOI_Malloc(sizeof(ADIO_Fcntl_t));
	ADIO_Fcntl(fd, ADIO_FCNTL_GET_FSIZE, fcntl_struct, error_code);

	curr_fsize = fcntl_struct->fsize;

	alloc_size = diskspace;

	size = ADIOI_MIN(curr_fsize, alloc_size);

	ntimes = (size + ADIOI_PREALLOC_BUFSZ - 1)/ADIOI_PREALLOC_BUFSZ;
	buf = (char *) ADIOI_Malloc(ADIOI_PREALLOC_BUFSZ);
	done = 0;

	for (i=0; i<ntimes; i++) {
	    len = ADIOI_MIN(size-done, ADIOI_PREALLOC_BUFSZ);
	    ADIO_ReadContig(fd, buf,
                      len,

                      MPI_BYTE, ADIO_EXPLICIT_OFFSET, done,
			    &status, error_code);
	    if (*error_code != MPI_SUCCESS) {
		*error_code = MPIO_Err_create_code(MPI_SUCCESS,
						   MPIR_ERR_RECOVERABLE,
						   myname, __LINE__,
						   MPI_ERR_IO,
						   "**iopreallocrdwr",
						   0);
                return;
	    }
	    ADIO_WriteContig(fd, buf,
                       len,

                       MPI_BYTE, ADIO_EXPLICIT_OFFSET,
                             done, &status, error_code);
	    if (*error_code != MPI_SUCCESS) return;
	    done += len;
	}

	if (alloc_size > curr_fsize) {
	    memset(buf, 0, ADIOI_PREALLOC_BUFSZ);
	    size = alloc_size - curr_fsize;
	    ntimes = (size + ADIOI_PREALLOC_BUFSZ - 1)/ADIOI_PREALLOC_BUFSZ;
	    for (i=0; i<ntimes; i++) {
		len = ADIOI_MIN(alloc_size-done, ADIOI_PREALLOC_BUFSZ);
		ADIO_WriteContig(fd, buf,
                     len,

                     MPI_BYTE, ADIO_EXPLICIT_OFFSET,
				 done, &status, error_code);
		if (*error_code != MPI_SUCCESS) return;
		done += len;
	    }
	}
	ADIOI_Free(fcntl_struct);
	ADIOI_Free(buf);
	*error_code = MPI_SUCCESS;
}
