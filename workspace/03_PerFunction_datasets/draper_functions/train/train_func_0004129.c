split_der(asn1buf *buf, unsigned char *const *der, size_t len,
          taginfo *tag_out, size_t *len_out)
{
    asn1_error_code ret;
    const unsigned char *contents, *remainder;
    size_t clen, rlen;

    ret = get_tag(*der, len, tag_out, &contents, &clen, &remainder, &rlen);
    if (ret)
        return ret;
    if (rlen != 0)
        return ASN1_BAD_LENGTH;
    *len_out = clen;
    return asn1buf_insert_bytestring(buf, clen, contents);
}
