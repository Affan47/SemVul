unpack_struct(char *dest, char *src, int srclen, int num, MPI_Datatype dtype)
{
	int		i, j;
	int		size;
	int		blksize;
	int		extent;
	int		*blklen;
	MPI_Aint	*disp;
	MPI_Datatype	*type;
	char		*d;
	char		*start;

	start = src;
	extent = dtype->dt_upper - dtype->dt_lower;

	for (i = 0; i < num; ++i, dest += extent) {

	    d = dest;
	    blklen = dtype->dt_lengths;
	    disp = dtype->dt_disps;
	    type = dtype->dt_dtypes;

	    for (j = 0; j < dtype->dt_count; ++j, ++blklen, ++disp, ++type) {

		blksize = *blklen * (*type)->dt_size;

		if (blksize > 0) {

		    size = unpack(d + *disp, src, srclen, *blklen, *type);
		    src += size;

		    if (size != blksize) {
			return(src - start);
		    } else {
			srclen -= blksize;
		    }
		}
	    }
	}

	return(src - start);
}
