__free_buffer_wake(struct dm_buffer *b)
{
	struct dm_bufio_client *c = b->c;

	if (!c->need_reserved_buffers)
		free_buffer(b);
	else {
		list_add(&b->lru_list, &c->reserved_buffers);
		c->need_reserved_buffers--;
	}

	wake_up(&c->free_buffer_wait);
}
