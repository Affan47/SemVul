ADIOI_Get_eof_offset(ADIO_File fd, ADIO_Offset *eof_offset)
{
    unsigned filetype_size;
    int error_code, filetype_is_contig, etype_size;
    ADIO_Offset fsize, disp, sum=0, size_in_file, n_filetypes, rem;
    int flag, i;
    ADIO_Fcntl_t *fcntl_struct;
    MPI_Aint filetype_extent;
    ADIOI_Flatlist_node *flat_file;


    fcntl_struct = (ADIO_Fcntl_t *) ADIOI_Malloc(sizeof(ADIO_Fcntl_t));
    ADIO_Fcntl(fd, ADIO_FCNTL_GET_FSIZE, fcntl_struct, &error_code);
    fsize = fcntl_struct->fsize;
    ADIOI_Free(fcntl_struct);


    ADIOI_Datatype_iscontig(fd->filetype, &filetype_is_contig);
    etype_size = fd->etype_size;

    if (filetype_is_contig)
	*eof_offset = (fsize - fd->disp + etype_size - 1)/etype_size;

    else {

	flat_file = ADIOI_Flatlist;
	while (flat_file->type != fd->filetype)
	    flat_file = flat_file->next;

	MPI_Type_size(fd->filetype, (int*)&filetype_size);
	MPI_Type_extent(fd->filetype, &filetype_extent);

	disp = fd->disp;
	n_filetypes = -1;
	flag = 0;
	while (!flag) {
	    sum = 0;
	    n_filetypes++;
	    for (i=0; i<flat_file->count; i++) {
		sum += flat_file->blocklens[i];
		if (disp + flat_file->indices[i] +
		    n_filetypes* ADIOI_AINT_CAST_TO_OFFSET filetype_extent +
		       flat_file->blocklens[i] >= fsize) {
		    if (disp + flat_file->indices[i] +
			   n_filetypes * ADIOI_AINT_CAST_TO_OFFSET filetype_extent >= fsize)
			sum -= flat_file->blocklens[i];
		    else {
			rem = (disp + flat_file->indices[i] +
				n_filetypes* ADIOI_AINT_CAST_TO_OFFSET filetype_extent
				+ flat_file->blocklens[i] - fsize);
			sum -= rem;
		    }
		    flag = 1;
		    break;
		}
	    }
	}
	size_in_file = n_filetypes*(ADIO_Offset)filetype_size + sum;
	*eof_offset = (size_in_file+etype_size-1)/etype_size;
    }
}
