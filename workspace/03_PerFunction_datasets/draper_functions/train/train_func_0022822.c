fill_buffer(ByteIOContext *s)
{
    uint8_t *dst= !s->max_packet_size && s->buf_end - s->buffer < s->buffer_size ? s->buf_ptr : s->buffer;
    int len= s->buffer_size - (dst - s->buffer);

    assert(s->buf_ptr == s->buf_end);


    if (s->eof_reached)
        return;

    if(s->update_checksum && dst == s->buffer){
        if(s->buf_end > s->checksum_ptr)
            s->checksum= s->update_checksum(s->checksum, s->checksum_ptr, s->buf_end - s->checksum_ptr);
        s->checksum_ptr= s->buffer;
    }

    if(s->read_packet)
        len = s->read_packet(s->opaque, dst, len);
    else
        len = 0;
    if (len <= 0) {


        s->eof_reached = 1;
        if(len<0)
            s->error= len;
    } else {
        s->pos += len;
        s->buf_ptr = dst;
        s->buf_end = dst + len;
    }
}
