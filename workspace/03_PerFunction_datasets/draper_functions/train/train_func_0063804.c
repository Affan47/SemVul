tns_outbuf_to_bstring(tns_outbuf *outbuf)
{
    if(outbuf->used_size == outbuf->alloc_size) {
        tns_outbuf_extend(outbuf);
    }

    tns_inplace_reverse(outbuf->buffer, outbuf->used_size);

    bstring b = malloc(sizeof(struct tagbstring));
    b->slen = outbuf->used_size;
    b->data = (unsigned char *)outbuf->buffer;
    b->data[b->slen] = '\0';
    b->mlen = outbuf->alloc_size;

    return b;
}
