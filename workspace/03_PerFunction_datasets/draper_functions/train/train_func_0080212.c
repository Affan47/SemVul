__adf_nbuf_trim_tail(__adf_nbuf_t buf, adf_os_size_t len)
{
    VDESC *last_desc = __adf_nbuf_last(buf);

    adf_os_assert(buf != NULL);
    last_desc->data_size -= len;
    buf->buf_length -= len;


}
