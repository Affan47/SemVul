add_to_buffer(
    ipc_binary_buf_t *buf,
    gsize size,
    gpointer data)
{
    expand_buffer(buf, size);

    g_memmove(buf->buf + buf->offset + buf->length, data, size);
    buf->length += size;
}
