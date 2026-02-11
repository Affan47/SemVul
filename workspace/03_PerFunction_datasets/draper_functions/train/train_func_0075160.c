__remove_assoc_queue(struct buffer_head *bh)
{
	list_del_init(&bh->b_assoc_buffers);
	WARN_ON(!bh->b_assoc_map);
	if (buffer_write_io_error(bh))
		set_bit(AS_EIO, &bh->b_assoc_map->flags);
	bh->b_assoc_map = NULL;
}
