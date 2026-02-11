lwpb_decode_32bit(struct lwpb_buf *buf, u32_t *value)
{
    if (lwpb_buf_left(buf) < 4)
        return LWPB_ERR_END_OF_BUF;

    *value = buf->pos[0] | (buf->pos[1] << 8) |
             (buf->pos[2] << 16) | (buf->pos[3] << 24);
    buf->pos += 4;

    return LWPB_ERR_OK;
}
