yajl_buf_append(yajl_buf buf, const void * data, size_t len)
{
    yajl_buf_ensure_available(buf, len);
    if (len > 0) {
        assert(data != NULL);
        memcpy(buf->data + buf->used, data, len);
        buf->used += len;
        buf->data[buf->used] = 0;
    }
}
