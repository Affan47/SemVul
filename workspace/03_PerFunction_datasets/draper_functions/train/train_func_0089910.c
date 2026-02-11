HeapIO_Seek (inbuf_t *bp, long offset)
{
    if (bp->file == NULL) {

	Byte_t	*newPos = bp->base + offset;
	if (bp->buf + bp->nbytes <= newPos)
	    return FAILURE;
	else {
	    bp->nbytes -= (newPos - bp->buf);
	    bp->buf = newPos;
	    return SUCCESS;
	}
    }
    else {
      if (fseek (bp->file, offset, SEEK_SET) != 0)
	Die ("unable to seek on heap image\n");
      bp->nbytes = 0;
    }

}
