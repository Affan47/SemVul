lam_unpack(char *src, int srclen, char *dest, int count, MPI_Datatype dtype)
{
	int		size;

	if (srclen < 0) {
		return(LAMERROR);
	}


	size = count * dtype->dt_size;
	srclen = LAM_min(size, srclen);

	if (srclen == 0) {
		return(0);
	}


#if LAM_WORDS_BIGENDIAN
	size = unpack(dest, src, srclen, count, dtype);
#else
	if (lam_homog) {
		size = unpack(dest, src, srclen, count, dtype);
	} else {
		size = unpack_rev(dest, src, srclen, count, dtype);
	}
#endif

	return(size);
}
