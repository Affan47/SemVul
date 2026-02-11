deliver_data(SSCOP_DSC *dsc)
{
    BUFFER *buf;

    if (!dsc->clear_buffers) {
	while ((buf = queue_get(&dsc->rx_buf))) {
	    if (dsc->ops->data_ind)
		dsc->ops->data_ind(dsc->user,buf->data,buf->length,buf->key);
	    buffer_discard(buf);
	}
    }
    clear_receive_buffer(dsc);
}
