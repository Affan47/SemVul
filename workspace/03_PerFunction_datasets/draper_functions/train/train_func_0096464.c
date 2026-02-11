bam_circbuf_create_staged(const int size)
{
	bam_circbuf * cbuf = bam_circbuf_create(size);

	if(cbuf == NULL)
		return NULL;

	cbuf->stage = malloc(size);

	if(cbuf->stage == NULL)
	{
		bam_circbuf_destroy(&cbuf);
		return NULL;
	}

	return cbuf;
}
