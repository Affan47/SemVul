consume_from_buffer(
    ipc_binary_buf_t *buf,
    gsize size)
{
    g_assert(size <= buf->length);

    buf->length -= size;
    if (buf->length == 0)
	buf->offset = 0;
    else
	buf->offset += size;
}
