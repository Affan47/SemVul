build_cb_config_list(ADIO_File fd,
	MPI_Comm orig_comm, MPI_Comm comm,
	int rank, int procs, int *error_code)
{
    ADIO_cb_name_array array;
    int *tmp_ranklist;
    int rank_ct;
    char *value;
    static char myname[] = "ADIO_OPEN cb_config_list";


    ADIOI_cb_gather_name_array(orig_comm, comm, &array);


    if (rank == 0) {
	tmp_ranklist = (int *) ADIOI_Malloc(sizeof(int) * procs);
	if (tmp_ranklist == NULL) {
	    *error_code = MPIO_Err_create_code(*error_code,
					       MPIR_ERR_RECOVERABLE,
					       myname,
					       __LINE__,
					       MPI_ERR_OTHER,
					       "**nomem2",0);
	    return 0;
	}

	rank_ct = ADIOI_cb_config_list_parse(fd->hints->cb_config_list,
					     array, tmp_ranklist,
					     fd->hints->cb_nodes);


	if (rank_ct > 0) {
	    fd->hints->ranklist = (int *) ADIOI_Malloc(sizeof(int) * rank_ct);
	    memcpy(fd->hints->ranklist, tmp_ranklist, sizeof(int) * rank_ct);
	}
	ADIOI_Free(tmp_ranklist);
	fd->hints->cb_nodes = rank_ct;

	value = (char *) ADIOI_Malloc((MPI_MAX_INFO_VAL+1)*sizeof(char));
	ADIOI_Snprintf(value, MPI_MAX_INFO_VAL+1, "%d", rank_ct);
	ADIOI_Info_set(fd->info, "cb_nodes", value);
	ADIOI_Free(value);
    }

    ADIOI_cb_bcast_rank_map(fd);
    if (fd->hints->cb_nodes <= 0) {
	*error_code = MPIO_Err_create_code(MPI_SUCCESS, MPIR_ERR_RECOVERABLE,
					   myname, __LINE__, MPI_ERR_IO,
					   "**ioagnomatch", 0);
	fd = ADIO_FILE_NULL;
    }
    return 0;
}
