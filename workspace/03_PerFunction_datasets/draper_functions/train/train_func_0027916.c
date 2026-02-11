lam_pack(char *src, int count, MPI_Datatype dtype, char *dest, int destlen)
{
	int		size;


	size = count * dtype->dt_size;

	if (destlen < size) {
	    return(LAMERROR);
	}


	if (size > 0) {
#if LAM_WORDS_BIGENDIAN
		pack(dest, src, count, dtype);
#else
		if (lam_homog) {
			pack(dest, src, count, dtype);
		} else {
			pack_rev(dest, src, count, dtype);
		}
#endif
	}

	return(size);
}
