asn1buf_insert_octet(asn1buf *buf, const int o)
{
    asn1_error_code retval;

    retval = asn1buf_ensure_space(buf,1U);
    if (retval) return retval;
    *(buf->next) = (char)o;
    (buf->next)++;
    return 0;
}
