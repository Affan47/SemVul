submit_io(struct dm_buffer *b, int rw, sector_t block,
		      bio_end_io_t *end_io)
{
	if (rw == WRITE && b->c->write_callback)
		b->c->write_callback(b);

	if (b->c->block_size <= DM_BUFIO_INLINE_VECS * PAGE_SIZE &&
	    b->data_mode != DATA_MODE_VMALLOC)
		use_inline_bio(b, rw, block, end_io);
	else
		use_dmio(b, rw, block, end_io);
}
