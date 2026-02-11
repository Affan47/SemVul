comp_zlib_compress(unsigned char *prev_block, unsigned char *curr_block, unsigned char *out_block, int blk_size, int bufsize) {
	unsigned long dest_size;
	int retval;
	dest_size=(int) ((float) (blk_size*1.01)+13);

#ifdef HAVE_COMPRESS2
	retval=compress2(out_block, &dest_size, curr_block, blk_size, Z_BEST_COMPRESSION);
#else
	retval=compress(out_block, &dest_size, curr_block, blk_size);
#endif
	if (retval!=Z_OK) return(-1);

	dest_size-=2;
	if (out_block[0]!=120 || out_block[1]!=218) {
		PRINTERR("Error!  Invalid headers, output will most likely be unusable.");
		return(-1);
	}
	memmove(out_block, out_block+2, dest_size);

	return(dest_size);
}
