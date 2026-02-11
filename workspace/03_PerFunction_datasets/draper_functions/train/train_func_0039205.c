HeapIO_WriteImageHeader (writer_t *wr, int kind)
{
    ml_image_hdr_t	hdr;

    hdr.byteOrder = ORDER;
    hdr.magic	  = ((kind == EXPORT_HEAP_IMAGE) || (kind == EXPORT_FN_IMAGE))
			? IMAGE_MAGIC : BLAST_MAGIC;
    hdr.kind	  = kind;


    WR_Write(wr, &hdr, sizeof(hdr));
    if (WR_Error(wr))
	return FAILURE;
    else
	return SUCCESS;

}
