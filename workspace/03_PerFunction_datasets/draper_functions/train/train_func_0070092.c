bf_seek(struct bfile* bfp, long offset)
{
	if (offset < bfp->buffer_size) {
		bfp->buffer_pos = offset;
		return 0;
	} else {
		return 1;
	}
}
