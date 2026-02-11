asn1buf_size(const asn1buf *buf)
{
    if (buf == NULL || buf->base == NULL) return 0;
    return buf->bound - buf->base + 1;
}
