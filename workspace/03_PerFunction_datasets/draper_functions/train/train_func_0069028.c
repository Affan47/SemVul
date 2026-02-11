LZMA_close(void *handle)
{
struct lzma_handle_t *h = (struct lzma_handle_t *)handle;
if(h)
	{
	if(h->state == LZMA_STATE_WRITE)
		{
		LZMA_flush(h);
		LZMA_write_varint(h, 0);
		}
	if(h->dmem)
		{
		free(h->dmem);
		}
	if(h->mem)
		{
		free(h->mem);
		}
	close(h->fd);
	free(h);
	}
}
